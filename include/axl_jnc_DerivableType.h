// This file is part of AXL (R) Library
// Tibbo Technology Inc (C) 2004-2013. All rights reserved
// Author: Vladimir Gladkov

#pragma once

#include "axl_jnc_NamedType.h"
#include "axl_jnc_ImportType.h"
#include "axl_jnc_Function.h"

namespace axl {
namespace jnc {

class CDerivableType;
class CStructType;
class CClassType;
class CFunction;
class CProperty;

//.............................................................................

class CBaseTypeSlot: public CUserModuleItem
{
	friend class CDerivableType;
	friend class CStructType;
	friend class CClassType;

protected:
	CDerivableType* m_pType;
	CImportType* m_pType_i;

	size_t m_Offset;
	size_t m_VTableIndex;
	uint_t m_LlvmIndex;

public:
	CBaseTypeSlot ();

	uint_t
	GetFlags ()
	{
		return m_Flags;
	}

	CDerivableType*
	GetType ()
	{
		return m_pType;
	}

	CImportType*
	GetType_i ()
	{
		return m_pType_i;
	}

	size_t 
	GetOffset ()
	{
		return m_Offset;
	}

	size_t
	GetVTableIndex ()
	{
		return m_VTableIndex;
	}

	uint_t
	GetLlvmIndex ()
	{
		return m_LlvmIndex;
	}
};

//.............................................................................

class CBaseTypeCoord
{
protected:
	char m_Buffer [256];

public:
	CDerivableType* m_pType;
	size_t m_Offset;
	rtl::CArrayT <int32_t> m_LlvmIndexArray;
	size_t m_VTableIndex;
	size_t m_ParentNamespaceLevel;

public:
	CBaseTypeCoord ()
	{
		Init ();
	}

	CBaseTypeCoord (const CBaseTypeCoord& Coord)
	{
		Init ();
		*this = Coord;
	}

protected:
	void
	Init ();
};

//.............................................................................

class CDerivableType: public CNamedType
{
protected:
	// base types

	rtl::CStringHashTableMapT <CBaseTypeSlot*> m_BaseTypeMap;
	rtl::CStdListT <CBaseTypeSlot> m_BaseTypeList;
	rtl::CArrayT <CBaseTypeSlot*> m_ImportBaseTypeArray;

	// gc roots

	rtl::CArrayT <CBaseTypeSlot*> m_GcRootBaseTypeArray;
	rtl::CArrayT <CStructField*> m_GcRootMemberFieldArray;

	// members

	rtl::CArrayT <CStructField*> m_MemberFieldArray;
	rtl::CArrayT <CFunction*> m_MemberMethodArray;
	rtl::CArrayT <CProperty*> m_MemberPropertyArray;
	rtl::CArrayT <CStructField*> m_ImportFieldArray;
	
	// construction

	CFunction* m_pPreConstructor;
	CFunction* m_pConstructor;
	CFunction* m_pDefaultConstructor;
	CFunction* m_pStaticConstructor;
	CFunction* m_pStaticDestructor;
	CVariable* m_pStaticOnceFlagVariable; // 'once' semantics for static constructor

	// construct arrays

	rtl::CArrayT <CBaseTypeSlot*> m_BaseTypeConstructArray;
	rtl::CArrayT <CStructField*> m_MemberFieldConstructArray;
	rtl::CArrayT <CProperty*> m_MemberPropertyConstructArray;

	// overloaded operators

	rtl::CArrayT <CFunction*> m_UnaryOperatorTable;
	rtl::CArrayT <CFunction*> m_BinaryOperatorTable;
	rtl::CStringHashTableMapT <CFunction*> m_CastOperatorMap;
	CFunction* m_pCallOperator;

public:
	CDerivableType ();

	rtl::CConstListT <CBaseTypeSlot>
	GetBaseTypeList ()
	{
		return m_BaseTypeList;
	}

	CBaseTypeSlot*
	AddBaseType (CType* pType);

	CBaseTypeSlot*
	FindBaseType (CType* pType)
	{
		rtl::CStringHashTableMapIteratorT <CBaseTypeSlot*> It = m_BaseTypeMap.Find (pType->GetSignature ());
		return It ? It->m_Value : NULL;
	}

	bool
	FindBaseTypeTraverse (
		CType* pType,
		CBaseTypeCoord* pCoord = NULL
		)
	{
		return FindBaseTypeTraverseImpl (pType, pCoord, 0);
	}

	rtl::CArrayT <CStructField*> 
	GetMemberFieldArray ()
	{
		return m_MemberFieldArray;
	}

	rtl::CArrayT <CFunction*>
	GetMemberMethodArray ()
	{
		return m_MemberMethodArray;
	}

	rtl::CArrayT <CProperty*>
	GetMemberPropertyArray ()
	{
		return m_MemberPropertyArray;
	}
	
	bool
	CallBaseTypeConstructors (const CValue& ThisValue);

	bool
	CallMemberFieldConstructors (const CValue& ThisValue);

	bool
	CallMemberPropertyConstructors (const CValue& ThisValue);

	CFunction* 
	GetPreConstructor ()
	{
		return m_pPreConstructor;
	}

	CFunction* 
	GetConstructor ()
	{
		return m_pConstructor;
	}

	CFunction* 
	GetDefaultConstructor ();

	CFunction* 
	GetStaticConstructor ()
	{
		return m_pStaticConstructor;
	}

	CFunction* 
	GetStaticDestructor ()
	{
		return m_pStaticDestructor;
	}

	CVariable*
	GetStaticOnceFlagVariable ()
	{
		return m_pStaticOnceFlagVariable;
	}

	CFunction*
	GetUnaryOperator (EUnOp OpKind)
	{
		ASSERT ((size_t) OpKind < EUnOp__Count);
		return m_UnaryOperatorTable ? m_UnaryOperatorTable [OpKind] : NULL;
	}

	CFunction*
	GetBinaryOperator (EBinOp OpKind)
	{
		ASSERT ((size_t) OpKind < EBinOp__Count);
		return m_BinaryOperatorTable ? m_BinaryOperatorTable [OpKind] : NULL;
	}

	CFunction*
	GetCallOperator ()
	{
		return m_pCallOperator;
	}

	virtual
	CStructField*
	GetFieldByIndex (size_t Index) = 0;

	CStructField*
	CreateField (
		const rtl::CString& Name,
		CType* pType,
		size_t BitCount = 0,
		uint_t PtrTypeFlags = 0,
		rtl::CBoxListT <CToken>* pConstructor = NULL,
		rtl::CBoxListT <CToken>* pInitializer = NULL
		)
	{
		return CreateFieldImpl (Name, pType, BitCount, PtrTypeFlags, pConstructor, pInitializer);
	}

	CStructField*
	CreateField (
		CType* pType,
		size_t BitCount = 0,
		uint_t PtrTypeFlags = 0
		)
	{
		return CreateFieldImpl (rtl::CString (), pType, BitCount, PtrTypeFlags);
	}

	CFunction*
	CreateMethod (
		EStorage StorageKind,
		const rtl::CString& Name,
		CFunctionType* pShortType
		);

	CFunction*
	CreateUnnamedMethod (
		EStorage StorageKind,
		EFunction FunctionKind,
		CFunctionType* pShortType
		);

	CProperty*
	CreateProperty (
		EStorage StorageKind,
		const rtl::CString& Name,
		CPropertyType* pShortType
		);

	virtual
	bool
	AddMethod (CFunction* pFunction);

	virtual
	bool
	AddProperty (CProperty* pProperty);

protected:
	virtual
	CStructField*
	CreateFieldImpl (
		const rtl::CString& Name,
		CType* pType,
		size_t BitCount = 0,
		uint_t PtrTypeFlags = 0,
		rtl::CBoxListT <CToken>* pConstructor = NULL,
		rtl::CBoxListT <CToken>* pInitializer = NULL
		) = 0;

	bool
	ResolveImportBaseType (CBaseTypeSlot* pSlot);

	bool
	ResolveImportBaseTypes ();

	bool
	ResolveImportFields ();

	bool
	CreateDefaultMethod (
		EFunction FunctionKind,
		EStorage StorageKind = EStorage_Member
		);

	bool
	CompileDefaultStaticConstructor ();

	bool
	CompileDefaultConstructor ();

	bool
	FindBaseTypeTraverseImpl (
		CType* pType,
		CBaseTypeCoord* pCoord,
		size_t Level
		);

	virtual
	CModuleItem*
	FindItemTraverseImpl (
		const char* pName,
		CBaseTypeCoord* pCoord = NULL,
		uint_t Flags = 0
		)
	{
		return FindItemTraverseImpl (pName, pCoord, Flags, 0);
	}

	CModuleItem*
	FindItemTraverseImpl (
		const char* pName,
		CBaseTypeCoord* pCoord,
		uint_t Flags,
		size_t BaseTypeLevel
		);
};

//.............................................................................

} // namespace jnc {
} // namespace axl {
