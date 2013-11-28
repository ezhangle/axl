#include "pch.h"
#include "axl_jnc_Module.h"
#include "axl_jnc_Parser.llk.h"
#include "axl_io_MappedFile.h"

namespace axl {
namespace jnc {

//.............................................................................

void
CModule::Clear ()
{
	m_TypeMgr.Clear ();
	m_NamespaceMgr.Clear ();
	m_FunctionMgr.Clear ();
	m_VariableMgr.Clear ();
	m_ConstMgr.Clear ();
	m_ControlFlowMgr.Clear ();
	m_UnitMgr.Clear ();
	m_CalcLayoutArray.Clear ();
	m_CompileArray.Clear ();
	m_ApiItemArray.Clear ();
	m_LlvmDiBuilder.Clear ();

	m_Flags = 0;

	m_pConstructor = NULL;
	m_pDestructor = NULL;
	m_pLlvmModule = NULL;
}

bool
CModule::Create (
	const rtl::CString& Name,
	llvm::Module* pLlvmModule,
	uint_t Flags
	)
{
	Clear ();

	m_Flags = Flags;
	m_Name = Name;
	m_pLlvmModule = pLlvmModule;

	m_LlvmIrBuilder.Create ();

	if (Flags & EModuleFlag_DebugInfo)
		m_LlvmDiBuilder.Create ();

	return m_NamespaceMgr.AddStdItems ();
}

CModuleItem*
CModule::GetApiItem (
	size_t Slot,
	const char* pName
	)
{
	size_t Count = m_ApiItemArray.GetCount ();
	if (Count <= Slot)
		m_ApiItemArray.SetCount (Slot + 1);

	CModuleItem* pItem = m_ApiItemArray [Slot];
	if (pItem)
		return pItem;

	pItem = GetItemByName (pName);
	m_ApiItemArray [Slot] = pItem;
	return pItem;
}

bool
CModule::SetConstructor (CFunction* pFunction)
{
	if (!pFunction->GetType ()->GetArgArray ().IsEmpty ())
	{
		err::SetFormatStringError ("module 'construct' cannot have arguments");
		return false;
	}

	if (m_pConstructor)
	{
		err::SetFormatStringError ("module already has 'construct' method");
		return false;
	}

	pFunction->m_FunctionKind = EFunction_ModuleConstructor;
	pFunction->m_StorageKind = EStorage_Static;
	pFunction->m_Tag = "module.construct";
	m_pConstructor = pFunction;
	return true;
}

bool
CModule::SetDestructor (CFunction* pFunction)
{
	if (m_pDestructor)
	{
		err::SetFormatStringError ("module already has 'destruct' method");
		return false;
	}

	pFunction->m_FunctionKind = EFunction_ModuleDestructor;
	pFunction->m_StorageKind = EStorage_Static;
	pFunction->m_Tag = "module.destruct";
	m_pDestructor = pFunction;
	return true;
}

bool
CModule::SetFunctionPointer (
	llvm::ExecutionEngine* pLlvmExecutionEngine,
	const char* pName,
	void* pf
	)
{
	CFunction* pFunction = GetFunctionByName (pName);
	if (!pFunction)
		return false;

	llvm::Function* pLlvmFunction = pFunction->GetLlvmFunction ();
	if (!pLlvmFunction)
		return false;

	pLlvmExecutionEngine->addGlobalMapping (pLlvmFunction, pf);
	return true;
}

bool
CModule::SetFunctionPointer (
	llvm::ExecutionEngine* pLlvmExecutionEngine,
	const CQualifiedName& Name,
	void* pf
	)
{
	CModuleItem* pItem = m_NamespaceMgr.GetGlobalNamespace ()->FindItem (Name);
	if (!pItem || pItem->GetItemKind () != EModuleItem_Function)
		return false;

	llvm::Function* pLlvmFunction = ((CFunction*) pItem)->GetLlvmFunction ();
	if (!pLlvmFunction)
		return false;

	pLlvmExecutionEngine->addGlobalMapping (pLlvmFunction, pf);
	return true;
}

bool
CModule::Link (CModule* pModule)
{
	err::SetFormatStringError ("module link is not yet implemented");
	return false;
}

void
CModule::MarkForLayout (
	CModuleItem* pItem,
	bool IsForced
	)
{
	if (!IsForced && (pItem->m_Flags & EModuleItemFlag_NeedLayout))
		return;

	pItem->m_Flags |= EModuleItemFlag_NeedLayout;
	m_CalcLayoutArray.Append (pItem);
}

void
CModule::MarkForCompile (CModuleItem* pItem)
{
	if (pItem->m_Flags & EModuleItemFlag_NeedCompile)
		return;

	pItem->m_Flags |= EModuleItemFlag_NeedCompile;
	m_CompileArray.Append (pItem);
}

bool
CModule::Parse (
	const char* pFilePath,
	const char* pSource,
	size_t Length
	)
{
	bool Result;

	jnc::CScopeThreadModule ScopeModule (this);

	m_UnitMgr.CreateUnit (pFilePath);

	jnc::CLexer Lexer;
	Lexer.Create (pFilePath, pSource, Length);

	jnc::CParser Parser;
	Parser.Create (jnc::CParser::StartSymbol, true);

	for (;;)
	{
		const jnc::CToken* pToken = Lexer.GetToken ();
		if (pToken->m_Token == jnc::EToken_Eof)
			break;

		Result = Parser.ParseToken (pToken);
		if (!Result)
		{
			err::EnsureSrcPosError (pFilePath, pToken->m_Pos);
			return false;
		}

		Lexer.NextToken ();
	}

	return true;
}

bool
CModule::ParseFile (const char* pFilePath)
{
	io::CMappedFile File;
	bool Result = File.Open (pFilePath, io::EFileFlag_ReadOnly);
	if (!Result)
		return false;

	const char* p = (const char*) File.View ();
	size_t Length = (size_t) File.GetSize ();

	return p != NULL && Parse (pFilePath, p, Length);
}

bool
CModule::Compile ()
{
	bool Result;

	// step 1: resolve import types

	Result = m_TypeMgr.ResolveImportTypes ();
	if (!Result)
		return false;

	// step 2: calc layouts

	for (size_t i = 0; i < m_CalcLayoutArray.GetCount (); i++) // new items could be added in process
	{
		Result = m_CalcLayoutArray [i]->EnsureLayout ();
		if (!Result)
			return false;
	}

	// step 3: ensure module constructor (always! cause static variable might appear during compilation)

	if (m_pConstructor)
	{
		if (!m_pConstructor->HasBody ())
		{
			err::SetFormatStringError ("unresolved module constructor");
			return false;
		}

		Result = m_pConstructor->Compile ();
		if (!Result)
			return false;
	}
	else
	{
		Result = CreateDefaultConstructor ();
		if (!Result)
			return false;
	}

	// step 4: compile the rest

	for (size_t i = 0; i < m_CompileArray.GetCount (); i++) // new items could be added in process
	{
		Result = m_CompileArray [i]->Compile ();
		if (!Result)
			return false;
	}

	// step 5: ensure module destructor (if needed)

	if (!m_pDestructor && !m_VariableMgr.m_StaticDestructList.IsEmpty ())
		CreateDefaultDestructor ();

	// step 6: deal with tls

	Result =
		m_VariableMgr.CreateTlsStructType () &&
		m_FunctionMgr.InjectTlsPrologues ();

	if (!Result)
		return false;

	// step 7: delete unreachable blocks

	m_ControlFlowMgr.DeleteUnreachableBlocks ();

	// step 8: finalize debug information

	if (m_Flags & EModuleFlag_DebugInfo)
		m_LlvmDiBuilder.Finalize ();

	return true;
}

bool
CModule::CreateDefaultConstructor ()
{
	bool Result;

	ASSERT (!m_pConstructor);

	CFunctionType* pType = (CFunctionType*) GetSimpleType (EStdType_SimpleFunction);
	CFunction* pFunction = m_FunctionMgr.CreateFunction (EFunction_ModuleConstructor, pType);
	pFunction->m_StorageKind = EStorage_Static;
	pFunction->m_Tag = "module.construct";

	m_pConstructor = pFunction;

	m_FunctionMgr.InternalPrologue (pFunction);

	CBasicBlock* pBlock = m_ControlFlowMgr.SetCurrentBlock (pFunction->GetEntryBlock ());

	Result = m_VariableMgr.AllocatePrimeStaticVariables ();
	if (!Result)
		return false;

	m_ControlFlowMgr.SetCurrentBlock (pBlock);

	Result = m_VariableMgr.InitializeGlobalStaticVariables ();
	if (!Result)
		return false;

	m_FunctionMgr.InternalEpilogue ();

	return true;
}

void
CModule::CreateDefaultDestructor ()
{
	ASSERT (!m_pDestructor);

	CFunctionType* pType = (CFunctionType*) GetSimpleType (EStdType_SimpleFunction);
	CFunction* pFunction = m_FunctionMgr.CreateFunction (EFunction_ModuleDestructor, pType);
	pFunction->m_StorageKind = EStorage_Static;
	pFunction->m_Tag = "module.destruct";

	m_pDestructor = pFunction;

	m_FunctionMgr.InternalPrologue (pFunction);
	m_VariableMgr.m_StaticDestructList.RunDestructors ();
	m_FunctionMgr.InternalEpilogue ();
}

rtl::CString
CModule::GetLlvmIrString ()
{
	std::string String;
	llvm::raw_string_ostream Stream (String);
	m_pLlvmModule->print (Stream, NULL);
	return String.c_str ();
}

//.............................................................................

} // namespace jnc {
} // namespace axl {
