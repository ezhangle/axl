// This file is part of AXL (R) Library
// Tibbo Technology Inc (C) 2004-2013. All rights reserved
// Author: Vladimir Gladkov

#pragma once

#include "axl_jnc_Function.h"
#include "axl_jnc_Property.h"
#include "axl_jnc_ScheduleLauncherFunction.h"
#include "axl_jnc_ThunkFunction.h"
#include "axl_jnc_ThunkProperty.h"
#include "axl_jnc_PropertyTemplate.h"
#include "axl_jnc_ClassType.h"

namespace axl {
namespace jnc {

//.............................................................................

enum EStdFunc
{
	// void
	// jnc.RuntimeError (
	//		int Error,
	//		int8* pCodeAddr
	//		);

	EStdFunc_RuntimeError,

	// void
	// jnc.CheckNullPtr (
	//		int8* p,
	//		int Error
	//		);

	EStdFunc_CheckNullPtr,

	// void
	// jnc.CheckScopeLevel (
	//		size_t SrcScopeLevel
	//		size_t DstScopeLevel
	//		);

	EStdFunc_CheckScopeLevel,

	// void
	// jnc.CheckDataPtrRange (
	//		int8* p,
	//		size_t Size,
	//		int8* pRangeBegin,
	//		int8* pRangeEnd
	//		);

	EStdFunc_CheckDataPtrRange,

	// void
	// jnc.CheckClassPtrScopeLevel (
	//		object* p,
	//		size_t DstScopeLevel
	//		);

	EStdFunc_CheckClassPtrScopeLevel,

	// object*
	// jnc.DynamicCastClassPtr (
	//		object* p,
	//		int8* pType
	//		);

	EStdFunc_DynamicCastClassPtr,

	// object*
	// jnc.StrengthenClassPtr (weak object* p);

	EStdFunc_StrengthenClassPtr,

	// size_t
	// jnc.GetDataPtrSpan (jnc.DataPtr Ptr);

	EStdFunc_GetDataPtrSpan,

	// int8*
	// jnc.GcAllocate (
	//		int8* pType,
	//		size_t Count
	//		);

	EStdFunc_GcAllocate,

	// void
	// jnc.GcEnter ();

	EStdFunc_GcEnter,

	// void
	// jnc.GcLeave ();

	EStdFunc_GcLeave,

	// void
	// jnc.GcPulse ();

	EStdFunc_GcPulse,

	// void
	// jnc.MarkGcRoot (
	//		int8* p,
	//		int8* pType
	//		);

	EStdFunc_MarkGcRoot,

	// void
	// jnc.RunGc ();

	EStdFunc_RunGc,

	// i64
	// jnc.GetCurrentThreadId ();

	EStdFunc_GetCurrentThreadId,

	// i64
	// jnc.CreateThread (function* pf ());

	EStdFunc_CreateThread,

	// void
	// jnc.Sleep (uint_t MsCount);

	EStdFunc_Sleep,

	// uint64_t
	// jnc.getTimestamp ();

	EStdFunc_GetTimestamp,

	// size_t
	// strlen (nullable const char* p);

	EStdFunc_StrLen,

	// int
	// rand ();

	EStdFunc_Rand,

	// int
	// printf ();

	EStdFunc_Printf,

	// jnc.TTlsStruct*
	// jnc.GetTls ();

	EStdFunc_GetTls,

	// size_t
	// jnc.AppendFmtLiteral_a (
	//		jnc.TFmtLiteral* pLiteral,
	//		char* p,
	//		size_t Length
	//		);

	EStdFunc_AppendFmtLiteral_a,

	// size_t
	// jnc.AppendFmtLiteral_p (
	//		jnc.TFmtLiteral* pFmtLiteral,
	//		char* pFmtSpecifier,
	//		jnc.TPtr Ptr
	//		);

	EStdFunc_AppendFmtLiteral_p,

	// size_t
	// jnc.AppendFmtLiteral_i32 (
	//		jnc.TFmtLiteral* pFmtLiteral,
	//		char* pFmtSpecifier,
	//		i32 i
	//		);

	EStdFunc_AppendFmtLiteral_i32,

	// size_t
	// jnc.AppendFmtLiteral_ui32 (
	//		jnc.TFmtLiteral* pFmtLiteral,
	//		char* pFmtSpecifier,
	//		i32 i
	//		);

	EStdFunc_AppendFmtLiteral_ui32,

	// size_t
	// jnc.AppendFmtLiteral_i64 (
	//		jnc.TFmtLiteral* pFmtLiteral,
	//		char* pFmtSpecifier,
	//		i64 i
	//		);

	EStdFunc_AppendFmtLiteral_i64,

	// size_t
	// jnc.AppendFmtLiteral_ui64 (
	//		jnc.TFmtLiteral* pFmtLiteral,
	//		char* pFmtSpecifier,
	//		i64 i
	//		);

	EStdFunc_AppendFmtLiteral_ui64,

	// size_t
	// jnc.AppendFmtLiteral_f (
	//		jnc.TFmtLiteral* pFmtLiteral,
	//		char* pFmtSpecifier,
	//		double f
	//		);

	EStdFunc_AppendFmtLiteral_f,

	EStdFunc_SimpleMulticastCall,

	EStdFunc__Count
};

//.............................................................................

class CFunctionMgr
{
	friend class CModule;
	friend class CDerivableType;
	friend class CClassType;
	friend class CFunction;
	friend class CParser;

protected:
	struct TEmissionContext: rtl::TListLink
	{
		CFunction* m_pCurrentFunction;

		CNamespace* m_pCurrentNamespace;
		CScope* m_pCurrentScope;

		CBasicBlock* m_pCurrentBlock;
		CBasicBlock* m_pReturnBlock;
		CBasicBlock* m_pUnreachableBlock;
		uint_t m_ControlFlowMgrFlags;

		CValue m_ThisValue;
		CValue m_ScopeLevelValue;
		CValue m_VTablePtrPtrValue;
		CValue m_VTablePtrValue;

		llvm::DebugLoc m_LlvmDebugLoc;
	};

protected:
	CModule* m_pModule;

	// unfortunately LLVM does not provide a slot for back-pointer from llvm::Function, hence the map

	rtl::CHashTableMapT <llvm::Function*, CFunction*, rtl::CHashIdT <llvm::Function*> > m_LlvmFunctionMap;

	rtl::CStdListT <CFunction> m_FunctionList;
	rtl::CStdListT <CProperty> m_PropertyList;
	rtl::CStdListT <CPropertyTemplate> m_PropertyTemplateList;
	rtl::CStdListT <CScheduleLauncherFunction> m_ScheduleLauncherFunctionList;
	rtl::CStdListT <CThunkFunction> m_ThunkFunctionList;
	rtl::CStdListT <CThunkProperty> m_ThunkPropertyList;
	rtl::CStdListT <CDataThunkProperty> m_DataThunkPropertyList;
	rtl::CStringHashTableMapT <CFunction*> m_ThunkFunctionMap;
	rtl::CStringHashTableMapT <CProperty*> m_ThunkPropertyMap;
	rtl::CStringHashTableMapT <CFunction*> m_ScheduleLauncherFunctionMap;

	CFunction* m_pCurrentFunction;

	CValue m_ThisValue;
	CValue m_ScopeLevelValue;
	CValue m_VTablePtrPtrValue;
	CValue m_VTablePtrValue;

	rtl::CStdListT <TEmissionContext> m_EmissionContextStack;

	CFunction* m_StdFunctionArray [EStdFunc__Count];

public:
	CFunctionMgr ();

	CModule*
	GetModule ()
	{
		return m_pModule;
	}

	CFunction*
	GetCurrentFunction ()
	{
		return m_pCurrentFunction;
	}

	CFunction*
	SetCurrentFunction (CFunction* pFunction);

	CFunction*
	FindFunctionByLlvmFunction (llvm::Function* pLlvmFunction)
	{
		rtl::CHashTableMapIteratorT <llvm::Function*, CFunction*> It = m_LlvmFunctionMap.Find (pLlvmFunction);
		return It ? It->m_Value : NULL;
	}

	CProperty*
	GetCurrentProperty ()
	{
		return m_pCurrentFunction ? m_pCurrentFunction->GetProperty () : NULL;
	}

	CValue
	GetThisValue ()
	{
		return m_ThisValue;
	}

	CValue
	GetScopeLevelValue ()
	{
		return m_ScopeLevelValue;
	}

	void
	Clear ();

	rtl::CConstListT <CFunction>
	GetFunctionList ()
	{
		return m_FunctionList;
	}

	rtl::CConstListT <CProperty>
	GetPropertyList ()
	{
		return m_PropertyList;
	}

	rtl::CConstListT <CThunkFunction>
	GetThunkFunctionList ()
	{
		return m_ThunkFunctionList;
	}

	rtl::CConstListT <CThunkProperty>
	GetThunkPropertyList ()
	{
		return m_ThunkPropertyList;
	}

	rtl::CConstListT <CDataThunkProperty>
	GetDataThunkPropertyList ()
	{
		return m_DataThunkPropertyList;
	}

	CFunction*
	CreateFunction (
		EFunction FunctionKind,
		const rtl::CString& Name,
		const rtl::CString& QualifiedName,
		const rtl::CString& Tag,
		CFunctionType* pType
		);

	CFunction*
	CreateFunction (
		EFunction FunctionKind,
		CFunctionType* pType
		)
	{
		return CreateFunction (FunctionKind, rtl::CString (), rtl::CString (), rtl::CString (), pType);
	}

	CFunction*
	CreateFunction (
		EFunction FunctionKind,
		const rtl::CString& Tag,
		CFunctionType* pType
		)
	{
		return CreateFunction (FunctionKind, rtl::CString (), rtl::CString (), Tag, pType);
	}

	CFunction*
	CreateFunction (
		const rtl::CString& Name,
		const rtl::CString& QualifiedName,
		CFunctionType* pType
		)
	{
		return CreateFunction (EFunction_Named, Name, QualifiedName, QualifiedName, pType);
	}

	CProperty*
	CreateProperty (
		EProperty PropertyKind,
		const rtl::CString& Name,
		const rtl::CString& QualifiedName,
		const rtl::CString& Tag
		);

	CProperty*
	CreateProperty (EProperty PropertyKind)
	{
		return CreateProperty (PropertyKind, rtl::CString (), rtl::CString (), rtl::CString ());
	}

	CProperty*
	CreateProperty (
		EProperty PropertyKind,
		const rtl::CString& Tag
		)
	{
		return CreateProperty (PropertyKind, rtl::CString (), rtl::CString (), Tag);
	}

	CProperty*
	CreateProperty (
		const rtl::CString& Name,
		const rtl::CString& QualifiedName
		)
	{
		return CreateProperty (EProperty_Normal, Name, QualifiedName, QualifiedName);
	}

	CPropertyTemplate*
	CreatePropertyTemplate ();

	bool
	Prologue (
		CFunction* pFunction,
		const CToken::CPos& Pos
		);

	bool
	Epilogue ();

	bool
	FireOnChanged ();

	void
	InternalPrologue (
		CFunction* pFunction,
		CValue* pArgValueArray = NULL,
		size_t ArgCount = 0
		);

	void
	InternalEpilogue ();

	bool
	InjectTlsPrologues ();

	bool
	JitFunctions (llvm::ExecutionEngine* pExecutionEngine);

	// std functions

	CFunction*
	GetStdFunction (EStdFunc Func);

	CFunction*
	GetDirectThunkFunction (
		CFunction* pTargetFunction,
		CFunctionType* pThunkFunctionType,
		bool HasUnusedClosure = false
		);

	CProperty*
	GetDirectThunkProperty (
		CProperty* pTargetProperty,
		CPropertyType* pThunkPropertyType,
		bool HasUnusedClosure = false
		);

	CProperty*
	GetDirectDataThunkProperty (
		CVariable* pTargetVariable,
		CPropertyType* pThunkPropertyType,
		bool HasUnusedClosure = false
		);

	CFunction*
	GetScheduleLauncherFunction (
		CFunctionPtrType* pTargetFunctionPtrType,
		EClassPtrType SchedulerPtrTypeKind = EClassPtrType_Normal
		);

protected:
	void
	CreateThisValue ();

	void
	PushEmissionContext ();

	void
	PopEmissionContext ();

	void
	CutVTable ();

	void
	RestoreVTable ();

	void
	InjectTlsPrologue (CFunction* pFunction);

	// LLVM code support functions

	CFunction*
	CreateCheckNullPtr ();

	CFunction*
	CreateCheckScopeLevel ();

	CFunction*
	CreateCheckDataPtrRange ();

	CFunction*
	CreateCheckClassPtrScopeLevel ();

	CFunction*
	CreateGetDataPtrSpan ();
};

//.............................................................................

} // namespace jnc {
} // namespace axl {
