// This file is part of AXL (R) Library
// Tibbo Technology Inc (C) 2004-2012. All rights reserved
// Author: Vladimir Gladkov

#pragma once

#include "axl_jnc_PropertyType.h"
#include "axl_jnc_FunctionPtrType.h"

namespace axl {
namespace jnc {

//.............................................................................

enum EPropertyPtrType
{
	EPropertyPtrType_Normal = 0,
	EPropertyPtrType_Weak,
	EPropertyPtrType_Thin,
	EPropertyPtrType_Unsafe,
	EPropertyPtrType__Count,
};

const tchar_t*
GetPropertyPtrTypeKindString (EPropertyPtrType PtrTypeKind);

//. . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .

inline
EPropertyPtrType 
GetPropertyPtrTypeKindFromModifiers (int Modifiers)
{
	return 
		(Modifiers & ETypeModifier_Unsafe) ? EPropertyPtrType_Unsafe :
		(Modifiers & ETypeModifier_Weak) ? EPropertyPtrType_Weak : 
		(Modifiers & ETypeModifier_Thin) ? EPropertyPtrType_Thin : EPropertyPtrType_Normal;
}

//.............................................................................

class CPropertyPtrType: public CType
{
protected:
	friend class CTypeMgr;

	EPropertyPtrType m_PtrTypeKind;
	CPropertyType* m_pTargetType;

public:
	CPropertyPtrType ();

	EPropertyPtrType
	GetPtrTypeKind ()
	{
		return m_PtrTypeKind;
	}

	CPropertyType* 
	GetTargetType ()
	{
		return m_pTargetType;
	}

	bool
	HasClosure ()
	{
		return m_PtrTypeKind == EPropertyPtrType_Normal || m_PtrTypeKind == EPropertyPtrType_Weak;
	}

	CStructType* 
	GetPropertyPtrStructType ();

	CStructType* 
	GetPropertyPtrStructType_w ();

	CStructType* 
	GetAuPropertyPtrStructType_t ();

	CStructType* 
	GetAuPropertyPtrStructType_u ();

	CDataPtrType*
	GetAuDataPtrType (EType TypeKind);

	static
	rtl::CStringA
	CreateSignature (
		CPropertyType* pPropertyType,
		EType TypeKind,
		EPropertyPtrType PtrTypeKind,
		int Flags
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

class CPropertyPtrTypeTuple: public rtl::TListLink
{
protected:
	friend class CTypeMgr;

	CStructType* m_pPtrStructType;
	CStructType* m_pPtrStructType_w;
	CStructType* m_pAuPtrStructType_t;
	CStructType* m_pAuPtrStructType_u;

	CPropertyPtrType* m_PtrTypeArray [2] [EPropertyPtrType__Count] [2]; // ref x kind x nullable

public:
	CPropertyPtrTypeTuple ()
	{
		memset (this, 0, sizeof (CPropertyPtrTypeTuple));
	}
};

//.............................................................................

} // namespace jnc {
} // namespace axl {
