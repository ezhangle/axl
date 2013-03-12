#include "stdafx.h"
#include "axl_jnc_AutoEv.h"
#include "axl_jnc_Module.h"

namespace axl {
namespace jnc {

//.............................................................................

CAutoEv::CAutoEv ()
{
	m_ItemKind = EModuleItem_AutoEv;
	m_NamespaceKind = ENamespace_AutoEv;
	m_pItemDecl = this;
	m_pType = NULL;
	m_pStarter = NULL;
	m_pStopper = NULL;
	m_pParentClassType = NULL;

	m_pParentClassFieldMember = NULL;
	m_pFieldStructType = NULL;
	m_pBindSiteArrayField = NULL;
	m_pStaticDataVariable = NULL;

	m_BindSiteCount = 0;
}

bool
CAutoEv::Create (
	CAutoEvType* pType,
	rtl::CStdListT <CFunctionFormalArg>* pArgList
	)
{
	ASSERT (m_StorageKind);

	m_pType = pType;
	m_pStarter = m_pModule->m_FunctionMgr.CreateFunction (EFunction_AutoEvStarter, pType->GetStarterType (), pArgList);
	m_pStarter->m_StorageKind = m_StorageKind;
	m_pStarter->m_pParentNamespace = this;
	m_pStarter->m_pAutoEv = this;
	m_pStarter->m_Tag = m_Tag + _T(".Start");
	
	m_pStopper = m_pModule->m_FunctionMgr.CreateFunction (EFunction_AutoEvStopper, pType->GetStopperType ());
	m_pStopper->m_StorageKind = m_StorageKind;
	m_pStopper->m_pParentNamespace = this;
	m_pStopper->m_pAutoEv = this;
	m_pStopper->m_Tag = m_Tag + _T(".Stop");

	m_pFieldStructType = m_pModule->m_TypeMgr.CreateUnnamedStructType ();
	m_pFieldStructType->m_StorageKind = m_StorageKind;
	m_pFieldStructType->m_pParentNamespace = this;

	if (m_pParentClassType)
	{
		m_pParentClassFieldMember = m_pParentClassType->GetIfaceStructType ()->CreateFieldMember (m_pFieldStructType);
		m_pType = m_pType->GetAutoEvMemberType (m_pParentClassType);
		m_pStarter->ConvertToMethodMember (m_pParentClassType);
		m_pStopper->ConvertToMethodMember (m_pParentClassType);
	}

	rtl::CIteratorT <CFunctionFormalArg> Arg = m_pStarter->GetArgList ().GetHead ();
	for (; Arg; Arg++)
	{
		CStructField* pField = m_pFieldStructType->CreateFieldMember (Arg->GetName (), Arg->GetType ());
		if (!pField)
			return false;

		AddItem (pField);
	}

	return true;
}

CFunction* 
CAutoEv::CreateHandler ()
{
	CFunctionType* pHandlerType = (CFunctionType*) m_pModule->m_TypeMgr.GetStdType (EStdType_SimpleFunction);
	CFunction* pHandler = m_pModule->m_FunctionMgr.CreateFunction (EFunction_AutoEvHandler, pHandlerType);
	pHandler->m_StorageKind = m_StorageKind;
	pHandler->m_pParentNamespace = this;
	pHandler->m_pAutoEv = this;
	pHandler->m_Tag = m_Tag + _T(".Handler");

	if (m_pParentClassType)
		pHandler->ConvertToMethodMember (m_pParentClassType);

	return pHandler;
}

bool
CAutoEv::CalcLayout ()
{
	ASSERT (m_BindSiteCount);

	if (!m_VTable.IsEmpty ()) // done already
		return true;

	CType* pBindSiteType = m_pModule->m_TypeMgr.GetStdType (EStdType_AutoEvBindSite);
	CArrayType* pBindSiteArrayType = pBindSiteType->GetArrayType (m_BindSiteCount);
	m_pBindSiteArrayField = m_pFieldStructType->CreateFieldMember (pBindSiteArrayType);
	m_pFieldStructType->CalcLayout ();

	ASSERT (IsMember () || m_StorageKind == EStorage_Static);
	if (m_StorageKind == EStorage_Static)
	{
		m_pStaticDataVariable = m_pModule->m_VariableMgr.CreateVariable (
			EVariable_Global, 
			_T("static_field"),
			m_Tag + _T(".static_field"), 
			m_pFieldStructType
			);
	}
	
	m_VTable.SetCount (2);
	m_VTable [0] = m_pStarter;
	m_VTable [1] = m_pStopper;

	CreateVTablePtr ();
	return true;
}

void
CAutoEv::CreateVTablePtr ()
{
	char Buffer [256];
	rtl::CArrayT <llvm::Constant*> LlvmVTable (ref::EBuf_Stack, Buffer, sizeof (Buffer));

	size_t Count = m_VTable.GetCount ();
	LlvmVTable.SetCount (Count);

	for (size_t i = 0; i < Count; i++)
	{
		CFunction* pFunction = m_VTable [i];

		if (pFunction->GetStorageKind () == EStorage_Abstract)
			pFunction = pFunction->GetType ()->GetAbstractFunction ();

		LlvmVTable [i] = pFunction->GetLlvmFunction ();
	}
	
	CStructType* pVTableStructType = m_pType->GetVTableStructType ();

	llvm::Constant* pLlvmVTableConstant = llvm::ConstantStruct::get (
		(llvm::StructType*) pVTableStructType->GetLlvmType (),
		llvm::ArrayRef <llvm::Constant*> (LlvmVTable, Count)
		);

	rtl::CString VariableTag;
	VariableTag.Format (_T("%s.vtbl"), GetQualifiedName ());
	llvm::GlobalVariable* pLlvmVTableVariable = new llvm::GlobalVariable (
			*m_pModule->m_pLlvmModule,
			pVTableStructType->GetLlvmType (),
			false,
			llvm::GlobalVariable::ExternalLinkage,
			pLlvmVTableConstant,
			(const tchar_t*) VariableTag
			);

	m_VTablePtrValue.SetLlvmValue (
		pLlvmVTableVariable, 
		pVTableStructType->GetDataPtrType (EDataPtrType_Unsafe),
		EValue_Const
		);
}

//.............................................................................

} // namespace jnc {
} // namespace axl {
