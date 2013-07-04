// This file is part of AXL (R) Library
// Tibbo Technology Inc (C) 2004-2013. All rights reserved
// Author: Vladimir Gladkov

#pragma once

#include "axl_jnc_ClassType.h"

namespace axl {
namespace jnc {

//.............................................................................

class CClassPtrType: public CType
{
	friend class CTypeMgr;

protected:
	EClassPtrType m_PtrTypeKind;
	CClassType* m_pTargetType;

public:
	CClassPtrType ();

	EClassPtrType 
	GetPtrTypeKind ()
	{
		return m_PtrTypeKind;
	}

	CClassType* 
	GetTargetType ()
	{
		return m_pTargetType;
	}

	CClassPtrType*
	GetCheckedPtrType ()
	{
		return !(m_Flags & (EPtrTypeFlag_Checked | EPtrTypeFlag_Unsafe)) ?  
			m_pTargetType->GetClassPtrType (m_PtrTypeKind, m_Flags | EPtrTypeFlag_Checked) : 
			this;			
	}

	CClassPtrType*
	GetUnCheckedPtrType ()
	{
		return (m_Flags & EPtrTypeFlag_Checked) ?  
			m_pTargetType->GetClassPtrType (m_PtrTypeKind, m_Flags & ~EPtrTypeFlag_Checked) : 
			this;			
	}

	static
	rtl::CString
	CreateSignature (
		CClassType* pClassType,
		EType TypeKind,
		EClassPtrType PtrTypeKind,
		uint_t Flags
		);

protected:
	virtual 
	void
	PrepareTypeString ();

	virtual 
	void
	PrepareLlvmType ();
};

//.............................................................................

struct TClassPtrTypeTuple: rtl::TListLink
{
	CClassPtrType* m_PtrTypeArray [2] [2] [2] [2] [3]; // ref x kind x const x volatile x unsafe / checked
};

//.............................................................................

inline
bool
IsClassPtrType (
	CType* pType, 
	EClassType ClassTypeKind
	)
{
	return 
		(pType->GetTypeKindFlags () & ETypeKindFlag_ClassPtr) &&
		((CClassPtrType*) pType)->GetTargetType ()->GetClassTypeKind () == ClassTypeKind;
}

//.............................................................................

} // namespace jnc {
} // namespace axl {