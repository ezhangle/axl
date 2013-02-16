// This file is part of AXL (R) Library
// Tibbo Technology Inc (C) 2004-2012. All rights reserved
// Author: Vladimir Gladkov

#pragma once

#include "axl_jnc_BitFieldType.h"

namespace axl {
namespace jnc {

class CStructType;

//.............................................................................

class CStructBaseType: public rtl::TListLink
{
protected:
	friend class CStructType;

	CStructType* m_pType;
	size_t m_Offset;
	size_t m_LlvmIndex;

public:
	CStructBaseType ()
	{
		m_pType = NULL;
		m_Offset = 0;
		m_LlvmIndex = -1;
	}

	CStructType*
	GetType ()
	{
		return m_pType;
	}

	size_t 
	GetOffset ()
	{
		return m_Offset;
	}

	size_t
	GetLlvmIndex ()
	{
		return m_LlvmIndex;
	}
};

//. . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .

class CStructBaseTypeCoord
{
protected:
	friend class CStructType;

	char m_Buffer [256];

public:
	size_t m_Offset;
	rtl::CArrayT <size_t> m_LlvmIndexArray;

public:
	CStructBaseTypeCoord ()
	{
		Init ();
	}

	CStructBaseTypeCoord (const CStructBaseTypeCoord& Coord)
	{
		Init ();
		*this = Coord;
	}

protected:
	void
	Init ()
	{
		m_Offset = 0;
		m_LlvmIndexArray.SetBuffer (ref::EBuf_Field, m_Buffer, sizeof (m_Buffer));
	}
};

//.............................................................................

class CStructMember: public CNamedModuleItem
{
protected:
	friend class CStructType;
	
	CStructType* m_pParentStructType;
	CType* m_pType;
	CType* m_pDualType;
	int m_DataPtrTypeFlags;

	CType* m_pBitFieldBaseType;
	size_t m_BitCount;
	
	size_t m_Offset;
	size_t m_LlvmIndex;

public:
	CStructMember ();

	CStructType*
	GetParentStructType ()
	{
		return m_pParentStructType;
	}

	CType*
	GetType ()
	{
		return m_pType;
	}

	size_t
	GetOffset ()
	{
		return m_Offset;
	}

	size_t
	GetLlvmIndex ()
	{
		return m_LlvmIndex;
	}
};

//.............................................................................

class CStructType: public CNamedType
{
protected:
	friend class CTypeMgr;
	friend class CClassType;
	friend class CProperty;

	size_t m_AlignFactor;
	size_t m_PackFactor;
	size_t m_FieldActualSize;
	size_t m_FieldAlignedSize;

	rtl::CStringHashTableMapAT <CStructBaseType*> m_BaseTypeMap;
	rtl::CStdListT <CStructBaseType> m_BaseTypeList;
	rtl::CStdListT <CStructMember> m_MemberList;
	rtl::CArrayT <llvm::Type*> m_LlvmFieldTypeArray;
	CBitFieldType* m_pLastBitFieldType;
	size_t m_LastBitFieldOffset;

public:
	CStructType ();

	virtual
	size_t 
	GetAlignFactor ()
	{
		return m_AlignFactor;
	}

	size_t 
	GetPackFactor ()
	{
		return m_PackFactor;
	}

	size_t 
	GetFieldActualSize ()
	{
		return m_FieldActualSize;
	}

	size_t 
	GetFieldAlignedSize ()
	{
		return m_FieldAlignedSize;
	}

	rtl::CConstListT <CStructBaseType>
	GetBaseTypeList ()
	{
		return m_BaseTypeList;
	}

	bool
	FindBaseType (
		CStructType* pType,
		CStructBaseTypeCoord* pCoord = NULL
		)
	{
		return FindBaseTypeImpl (pType, pCoord, 0);
	}

	CStructBaseType*
	AddBaseType (CStructType* pType);

	CModuleItem*
	FindItemWithBaseTypeList (const tchar_t* pName);

	rtl::CConstListT <CStructMember>
	GetMemberList ()
	{
		return m_MemberList;
	}

	CStructMember*
	FindMember (
		const tchar_t* pName,
		CStructBaseTypeCoord* pBaseTypeCoord = NULL
		)
	{
		return FindMemberImpl (pName, pBaseTypeCoord, 0);
	}

	CStructMember*
	CreateMember (
		const rtl::CString& Name,
		CType* pType,
		size_t BitCount = 0
		);

	CStructMember*
	CreateMember (
		CType* pType,
		size_t BitCount = 0
		)
	{
		return CreateMember (rtl::CString (), pType, BitCount);
	}

	bool
	Append (CStructType* pType);

	virtual
	bool
	CalcLayout ();

protected:
	virtual 
	void
	PrepareTypeString ()
	{
		m_TypeString.Format (_T("struct %s"), m_Tag);
	}

	virtual 
	void
	PrepareLlvmType ()
	{
		m_pLlvmType = llvm::StructType::create (llvm::getGlobalContext (), (const tchar_t*) m_Tag);
	}

	bool
	FindBaseTypeImpl (
		CStructType* pType,
		CStructBaseTypeCoord* pCoord,
		size_t Level
		);

	CStructMember*
	FindMemberImpl (
		const tchar_t* pName,
		CStructBaseTypeCoord* pBaseTypeCoord,
		size_t BaseTypeLevel
		);

	void
	ResetLayout ();

	bool
	LayoutField (
		llvm::Type* pLlvmType,
		size_t Size,
		size_t AlignFactor,
		size_t* pOffset,
		size_t* pLlvmIndex
		);

	bool
	LayoutField (
		CType* pType,
		size_t* pOffset,
		size_t* pLlvmIndex
		)
	{
		return LayoutField (pType->GetLlvmType (), pType->GetSize (), pType->GetAlignFactor (), pOffset, pLlvmIndex);
	}

	bool
	LayoutBitField (
		CType* pBaseType,
		size_t BitCount,
		CType** ppType,
		size_t* pOffset,
		size_t* pLlvmIndex
		);

	size_t
	GetFieldOffset (size_t AlignFactor);

	size_t 
	GetBitFieldBitOffset (
		CType* pType,
		size_t BitCount
		);

	size_t
	SetFieldActualSize (size_t Size);

	CArrayType*
	InsertPadding (size_t Size);
};

//.............................................................................

} // namespace jnc {
} // namespace axl {
