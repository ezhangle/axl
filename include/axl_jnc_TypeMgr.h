// This file is part of AXL (R) Library
// Tibbo Technology Inc (C) 2004-2013. All rights reserved
// Author: Vladimir Gladkov

#pragma once

#include "axl_jnc_Type.h"
#include "axl_jnc_ArrayType.h"
#include "axl_jnc_BitFieldType.h"
#include "axl_jnc_EnumType.h"
#include "axl_jnc_StructType.h"
#include "axl_jnc_UnionType.h"
#include "axl_jnc_ClassType.h"
#include "axl_jnc_FunctionType.h"
#include "axl_jnc_PropertyType.h"
#include "axl_jnc_DataPtrType.h"
#include "axl_jnc_ClassPtrType.h"
#include "axl_jnc_FunctionPtrType.h"
#include "axl_jnc_PropertyPtrType.h"
#include "axl_jnc_ImportType.h"
#include "axl_jnc_AutoEvClassType.h"
#include "axl_jnc_ClosureClassType.h"
#include "axl_jnc_McSnapshotClassType.h"
#include "axl_jnc_MulticastClassType.h"

namespace axl {
namespace jnc {

class CModule;

//.............................................................................

class CTypeMgr
{
	friend class CModule;

protected:
	CModule* m_pModule;

	CType m_PrimitiveTypeArray [EType__PrimitiveTypeCount];
	CType* m_StdTypeArray [EStdType__Count];

	rtl::CStdListT <CArrayType> m_ArrayTypeList;
	rtl::CStdListT <CBitFieldType> m_BitFieldTypeList;
	rtl::CStdListT <CEnumType> m_EnumTypeList;
	rtl::CStdListT <CStructType> m_StructTypeList;
	rtl::CStdListT <CUnionType> m_UnionTypeList;
	rtl::CStdListT <CClassType> m_ClassTypeList;
	rtl::CStdListT <CFunctionType> m_FunctionTypeList;
	rtl::CStdListT <CPropertyType> m_PropertyTypeList;
	rtl::CStdListT <CDataPtrType> m_DataPtrTypeList;
	rtl::CStdListT <CClassPtrType> m_ClassPtrTypeList;
	rtl::CStdListT <CFunctionPtrType> m_FunctionPtrTypeList;
	rtl::CStdListT <CPropertyPtrType> m_PropertyPtrTypeList;
	rtl::CStdListT <CNamedImportType> m_NamedImportTypeList;
	rtl::CStdListT <CImportPtrType> m_ImportPtrTypeList;
	rtl::CStdListT <CAutoEvClassType> m_AutoEvClassTypeList;
	rtl::CStdListT <CFunctionClosureClassType> m_FunctionClosureClassTypeList;
	rtl::CStdListT <CPropertyClosureClassType> m_PropertyClosureClassTypeList;
	rtl::CStdListT <CDataClosureClassType> m_DataClosureClassTypeList;
	rtl::CStdListT <CMulticastClassType> m_MulticastClassTypeList;
	rtl::CStdListT <CMcSnapshotClassType> m_McSnapshotClassTypeList;
	
	rtl::CStdListT <CTypedef> m_TypedefList;
	rtl::CStdListT <CFunctionArg> m_FunctionArgList;

	rtl::CStdListT <TSimplePropertyTypeTuple> m_SimplePropertyTypeTupleList;
	rtl::CStdListT <TFunctionArgTuple> m_FunctionArgTupleList;
	rtl::CStdListT <TDataPtrTypeTuple> m_DataPtrTypeTupleList;
	rtl::CStdListT <TClassPtrTypeTuple> m_ClassPtrTypeTupleList;
	rtl::CStdListT <TFunctionPtrTypeTuple> m_FunctionPtrTypeTupleList;
	rtl::CStdListT <TPropertyPtrTypeTuple> m_PropertyPtrTypeTupleList;

	rtl::CStringHashTableMapAT <CType*> m_TypeMap;

	rtl::CArrayT <CClassType*> m_StaticDestructArray; // classes with static destructors 

	size_t m_UnnamedEnumTypeCounter;
	size_t m_UnnamedStructTypeCounter;
	size_t m_UnnamedUnionTypeCounter;
	size_t m_UnnamedClassTypeCounter;

public:
	CTypeMgr ();

	CModule* 
	GetModule ()
	{
		return m_pModule;
	}

	void
	Clear ();

	bool
	ResolveImportTypes ();

	rtl::CConstListT <CArrayType> 
	GetArrayTypeList ()
	{
		return m_ArrayTypeList;
	}
	
	rtl::CConstListT <CBitFieldType> 
	GetBitFieldTypeList ()
	{
		return m_BitFieldTypeList;
	}
	
	rtl::CConstListT <CEnumType> 
	GetEnumTypeList ()
	{
		return m_EnumTypeList;
	}

	rtl::CConstListT <CStructType> 
	GetStructTypeList ()
	{
		return m_StructTypeList;
	}

	rtl::CConstListT <CUnionType> 
	GetUnionTypeList ()
	{
		return m_UnionTypeList;
	}

	rtl::CConstListT <CClassType> 
	GetClassTypeList ()
	{
		return m_ClassTypeList;
	}

	rtl::CConstListT <CFunctionType> 
	GetFunctionTypeList ()
	{
		return m_FunctionTypeList;
	}

	rtl::CConstListT <CPropertyType> 
	GetPropertyTypeList ()
	{
		return m_PropertyTypeList;
	}

	rtl::CConstListT <CDataPtrType> 
	GetDataPtrTypeList ()
	{
		return m_DataPtrTypeList;
	}

	rtl::CConstListT <CClassPtrType> 
	GetClassPtrTypeList ()
	{
		return m_ClassPtrTypeList;
	}

	rtl::CConstListT <CFunctionPtrType> 
	GetFunctionPtrTypeList ()
	{
		return m_FunctionPtrTypeList;
	}

	rtl::CConstListT <CPropertyPtrType> 
	GetPropertyPtrTypeList ()
	{
		return m_PropertyPtrTypeList;
	}

	rtl::CConstListT <CNamedImportType> 
	GetNamedImportTypeList ()
	{
		return m_NamedImportTypeList;
	}

	rtl::CConstListT <CImportPtrType> 
	GetImportPtrTypeList ()
	{
		return m_ImportPtrTypeList;
	}

	rtl::CConstListT <CAutoEvClassType> 
	GetAutoEvClassTypeList ()
	{
		return m_AutoEvClassTypeList;
	}

	rtl::CConstListT <CFunctionClosureClassType> 
	GetFunctionClosureClassTypeList ()
	{
		return m_FunctionClosureClassTypeList;
	}

	rtl::CConstListT <CPropertyClosureClassType> 
	GetPropertyClosureClassTypeList ()
	{
		return m_PropertyClosureClassTypeList;
	}

	rtl::CConstListT <CDataClosureClassType> 
	GetDataClosureClassTypeList ()
	{
		return m_DataClosureClassTypeList;
	}

	rtl::CConstListT <CMulticastClassType> 
	GetMulticastClassTypeList ()
	{
		return m_MulticastClassTypeList;
	}

	rtl::CConstListT <CMcSnapshotClassType> 
	GetMcSnapshotClassTypeList ()
	{
		return m_McSnapshotClassTypeList;
	}

	rtl::CConstListT <CTypedef> 
	GetTypedefList ()
	{
		return m_TypedefList;
	}

	rtl::CArrayT <CClassType*> 
	GetStaticDestructArray ()
	{
		return m_StaticDestructArray;
	}

	CType* 
	GetPrimitiveType (EType TypeKind)
	{
		ASSERT (TypeKind < EType__PrimitiveTypeCount);
		return &m_PrimitiveTypeArray [TypeKind];
	}

	CType*
	GetStdType (EStdType StdType);

	CType*
	GetInt32Type (int32_t Integer)
	{
		return GetPrimitiveType (GetInt32TypeKind (Integer));
	}

	CType*
	GetUInt32Type (uint32_t Integer)
	{
		return GetPrimitiveType (GetInt32TypeKind_u (Integer));
	}

	CType*
	GetInt64Type (int64_t Integer)
	{
		return GetPrimitiveType (GetInt64TypeKind (Integer));
	}

	CType*
	GetInt64Type_u (uint64_t Integer)
	{
		return GetPrimitiveType (GetInt64TypeKind_u (Integer));
	}

	CBitFieldType* 
	GetBitFieldType (
		CType* pBaseType,
		size_t BitOffset,
		size_t BitCount
		);

	CArrayType* 
	GetArrayType (
		CType* pElementType,
		size_t ElementCount
		);

	CArrayType* 
	GetArrayType (
		EType ElementTypeKind,
		size_t ElementCount
		)
	{
		return GetArrayType (GetPrimitiveType (ElementTypeKind), ElementCount);
	}

	CArrayType* 
	GetLiteralType (size_t Length)
	{
		return GetArrayType (EType_Char, Length + 1);
	}

	CArrayType* 
	GetLiteralType_w (size_t Length)
	{
		return GetArrayType (EType_WChar, Length + 1);
	}

	CTypedef*
	CreateTypedef (
		const rtl::CString& Name,
		const rtl::CString& QualifiedName,
		CType* pType
		);

	CEnumType* 
	CreateEnumType (
		const rtl::CString& Name,
		const rtl::CString& QualifiedName,
		CType* pBaseType = NULL,
		uint_t Flags = 0
		);

	CEnumType* 
	CreateUnnamedEnumType (CType* pBaseType = NULL)
	{
		return CreateEnumType (rtl::CString (), rtl::CString (), pBaseType = NULL);
	}

	CStructType* 
	CreateStructType (
		const rtl::CString& Name,
		const rtl::CString& QualifiedName,
		size_t PackFactor = 8
		);

	CStructType* 
	CreateUnnamedStructType (size_t PackFactor = 8)
	{
		return CreateStructType (rtl::CString (), rtl::CString (), PackFactor);
	}

	CStructType* 
	GetStructType (
		CType** ppMemberTypeArray,
		size_t MemberCount,
		size_t PackFactor = 8
		);

	CUnionType* 
	CreateUnionType (
		const rtl::CString& Name,
		const rtl::CString& QualifiedName
		);

	CUnionType* 
	CreateUnnamedUnionType ()
	{
		return CreateUnionType (rtl::CString (), rtl::CString ());
	}

	CClassType* 
	CreateClassType (	
		EClassType ClassTypeKind,
		const rtl::CString& Name,
		const rtl::CString& QualifiedName,
		size_t PackFactor = 8
		);

	CClassType* 
	CreateClassType (	
		const rtl::CString& Name,
		const rtl::CString& QualifiedName,
		size_t PackFactor = 8
		)
	{
		return CreateClassType (EClassType_Normal, Name, QualifiedName, PackFactor);
	}

	CClassType* 
	CreateUnnamedClassType (
		EClassType ClassTypeKind,	
		size_t PackFactor = 8
		)
	{
		return CreateClassType (ClassTypeKind,	rtl::CString (), rtl::CString (), PackFactor);
	}

	CClassType* 
	CreateUnnamedClassType (size_t PackFactor = 8)
	{
		return CreateClassType (EClassType_Normal, rtl::CString (), rtl::CString (), PackFactor);
	}

	CClassType* 
	GetBoxClassType (CType* pBaseType);

	CFunctionArg*
	CreateFunctionArg (
		const rtl::CString& Name,
		CType* pType,
		uint_t PtrTypeFlags = 0,
		rtl::CBoxListT <CToken>* pInitializer = NULL
		);

	CFunctionArg*
	GetSimpleFunctionArg (
		EStorage StorageKind,
		CType* pType,
		uint_t PtrTypeFlags = 0
		);

	CFunctionArg*
	GetSimpleFunctionArg (
		CType* pType,
		uint_t PtrTypeFlags = 0
		)
	{
		return GetSimpleFunctionArg (EStorage_Stack, pType, PtrTypeFlags);
	}

	CFunctionType* 
	GetFunctionType (
		ECallConv CallConv,
		CType* pReturnType,
		const rtl::CArrayT <CFunctionArg*>& ArgArray,
		uint_t Flags = 0
		);

	CFunctionType* 
	GetFunctionType (
		CType* pReturnType,
		const rtl::CArrayT <CFunctionArg*>& ArgArray,
		uint_t Flags = 0
		)
	{
		return GetFunctionType (ECallConv_Default, pReturnType, ArgArray, Flags);
	}

	CFunctionType* 
	GetFunctionType (	
		ECallConv CallConv,
		CType* pReturnType,
		CType* const* ppArgType,
		size_t ArgCount,
		uint_t Flags = 0
		);

	CFunctionType* 
	GetFunctionType (	
		CType* pReturnType,
		CType* const* ppArgType,
		size_t ArgCount,
		uint_t Flags = 0
		)
	{
		return GetFunctionType (ECallConv_Default, pReturnType, ppArgType, ArgCount, Flags);
	}

	CFunctionType* 
	CreateUserFunctionType (
		ECallConv CallConv,
		CType* pReturnType,
		const rtl::CArrayT <CFunctionArg*>& ArgArray,
		uint_t Flags = 0
		);

	CFunctionType* 
	CreateUserFunctionType (
		CType* pReturnType,
		const rtl::CArrayT <CFunctionArg*>& ArgArray,
		uint_t Flags = 0
		)
	{
		return CreateUserFunctionType (ECallConv_Default, pReturnType, ArgArray, Flags);
	}

	CFunctionType* 
	GetMemberMethodType (
		CNamedType* pParentType,
		CFunctionType* pFunctionType,
		uint_t ThisArgPtrTypeFlags = 0
		);

	CFunctionType* 
	GetStdObjectMemberMethodType (CFunctionType* pFunctionType);

	CPropertyType* 
	GetPropertyType (
		CFunctionType* pGetterType,
		const CFunctionTypeOverload& SetterType,
		uint_t Flags = 0
		);

	CPropertyType* 
	GetSimplePropertyType (
		ECallConv CallConv,
		CType* pReturnType,
		uint_t Flags = 0
		);

	CPropertyType* 
	GetSimplePropertyType (
		CType* pReturnType,
		uint_t Flags = 0
		)
	{
		return GetSimplePropertyType (ECallConv_Default, pReturnType, Flags);
	}

	CPropertyType* 
	GetIndexedPropertyType (
		ECallConv CallConv,
		CType* pReturnType,
		CType* const* ppIndexArgType,
		size_t IndexArgCount,
		uint_t Flags = 0
		);

	CPropertyType* 
	GetIndexedPropertyType (
		CType* pReturnType,
		CType* const* ppIndexArgType,
		size_t IndexArgCount,
		uint_t Flags = 0
		)
	{
		return GetIndexedPropertyType (ECallConv_Default, pReturnType, ppIndexArgType, IndexArgCount, Flags);
	}

	CPropertyType* 
	GetIndexedPropertyType (
		ECallConv CallConv,
		CType* pReturnType,
		const rtl::CArrayT <CFunctionArg*>& ArgArray,
		uint_t Flags = 0
		);

	CPropertyType* 
	GetIndexedPropertyType (
		CType* pReturnType,
		const rtl::CArrayT <CFunctionArg*>& ArgArray,
		uint_t Flags = 0
		)
	{
		return GetIndexedPropertyType (ECallConv_Default, pReturnType, ArgArray, Flags);
	}

	CPropertyType* 
	CreateIndexedPropertyType (
		ECallConv CallConv,
		CType* pReturnType,
		const rtl::CArrayT <CFunctionArg*>& ArgArray,
		uint_t Flags = 0
		);

	CPropertyType* 
	CreateIndexedPropertyType (
		CType* pReturnType,
		const rtl::CArrayT <CFunctionArg*>& ArgArray,
		uint_t Flags = 0
		)
	{
		return CreateIndexedPropertyType (ECallConv_Default, pReturnType, ArgArray, Flags);
	}

	CPropertyType* 
	GetMemberPropertyType (
		CNamedType* pParentType,
		CPropertyType* pPropertyType
		);

	CPropertyType* 
	GetStdObjectMemberPropertyType (CPropertyType* pPropertyType);

	CPropertyType* 
	GetShortPropertyType (CPropertyType* pPropertyType);

	CClassType* 
	GetMulticastType (
		CFunctionType* pFunctionType,
		EFunctionPtrType PtrTypeKind = EFunctionPtrType_Normal
		)
	{
		return GetMulticastType (GetFunctionPtrType (pFunctionType, PtrTypeKind));
	}

	CClassType* 
	GetMulticastType (CFunctionPtrType* pFunctionPtrType);

	CClassType* 
	GetAutoEvInterfaceType (CFunctionType* pStartMethodType);
	
	CAutoEvClassType* 
	CreateAutoEvType (
		const rtl::CString& Name,
		const rtl::CString& QualifiedName,
		CClassType* pIfaceType,
		CClassType* pParentType
		);

	CFunctionClosureClassType* 
	GetFunctionClosureClassType (
		CFunctionType* pTargetType,
		CFunctionType* pThunkType,
		CType* const* ppArgTypeArray,
		const size_t* pClosureMap,
		size_t ArgCount,
		uint64_t WeakMask
		);

	CPropertyClosureClassType* 
	GetPropertyClosureClassType (
		CPropertyType* pTargetType,
		CPropertyType* pThunkType,
		CType* const* ppArgTypeArray,
		const size_t* pClosureMap,
		size_t ArgCount,
		uint64_t WeakMask
		);

	CDataClosureClassType* 
	GetDataClosureClassType (
		CType* pTargetType,
		CPropertyType* pThunkType
		);

	CDataPtrType* 
	GetDataPtrType (
		CType* pDataType,
		EType TypeKind,
		EDataPtrType PtrTypeKind = EDataPtrType_Normal,
		uint_t Flags = 0
		);

	CDataPtrType* 
	GetDataPtrType (
		CType* pDataType,
		EDataPtrType PtrTypeKind = EDataPtrType_Normal,
		uint_t Flags = 0
		)
	{
		return GetDataPtrType (pDataType, EType_DataPtr, PtrTypeKind, Flags);
	}

	CStructType*
	GetDataPtrStructType (CType* pDataType);

	CClassPtrType* 
	GetClassPtrType (
		CClassType* pClassType,
		EType TypeKind,
		EClassPtrType PtrTypeKind = EClassPtrType_Normal,
		uint_t Flags = 0
		);

	CClassPtrType* 
	GetClassPtrType (
		CClassType* pClassType,
		EClassPtrType PtrTypeKind = EClassPtrType_Normal,
		uint_t Flags = 0
		)
	{
		return GetClassPtrType (pClassType, EType_ClassPtr, PtrTypeKind, Flags);	
	}

	CFunctionPtrType* 
	GetFunctionPtrType (
		CFunctionType* pFunctionType,
		EType TypeKind,
		EFunctionPtrType PtrTypeKind = EFunctionPtrType_Normal,
		uint_t Flags = 0
		);

	CFunctionPtrType* 
	GetFunctionPtrType (
		CFunctionType* pFunctionType,
		EFunctionPtrType PtrTypeKind = EFunctionPtrType_Normal,
		uint_t Flags = 0
		)
	{
		return GetFunctionPtrType (pFunctionType, EType_FunctionPtr, PtrTypeKind, Flags);
	}

	CStructType* 
	GetFunctionPtrStructType (CFunctionType* pFunctionType);

	CPropertyPtrType* 
	GetPropertyPtrType (
		CPropertyType* pPropertyType,
		EType TypeKind,
		EPropertyPtrType PtrTypeKind = EPropertyPtrType_Normal,
		uint_t Flags = 0
		);

	CPropertyPtrType* 
	GetPropertyPtrType (
		CPropertyType* pPropertyType,
		EPropertyPtrType PtrTypeKind = EPropertyPtrType_Normal,
		uint_t Flags = 0
		)
	{
		return GetPropertyPtrType (pPropertyType, EType_PropertyPtr, PtrTypeKind, Flags);
	}

	CStructType*
	GetPropertyVTableStructType (CPropertyType* pPropertyType);

	CStructType*
	GetPropertyPtrStructType (CPropertyType* pPropertyType);

	CNamedImportType*
	GetNamedImportType (	
		const CQualifiedName& Name,
		CNamespace* pAnchorNamespace
		);

	CImportPtrType*
	GetImportPtrType (	
		CNamedImportType* pImportType,
		uint_t TypeModifiers = 0,
		uint_t Flags = 0
		);

	CType*
	GetCheckedPtrType (CType* pType);

protected:
	TSimplePropertyTypeTuple*
	GetSimplePropertyTypeTuple (CType* pType);

	TFunctionArgTuple*
	GetFunctionArgTuple (CType* pType);

	TDataPtrTypeTuple*
	GetDataPtrTypeTuple (CType* pType);

	TClassPtrTypeTuple*
	GetClassPtrTypeTuple (CClassType* pClassType);

	TFunctionPtrTypeTuple*
	GetFunctionPtrTypeTuple (CFunctionType* pFunctionType);

	TPropertyPtrTypeTuple*
	GetPropertyPtrTypeTuple (CPropertyType* pPropertyType);

	void
	SetupAllPrimitiveTypes ();

	void
	SetupPrimitiveType (
		EType TypeKind,
		size_t Size,
		const char* pSignature
		);

	CStructType*
	CreateObjectHdrType ();

	CClassType*
	CreateObjectType ();

	CStructType* 
	CreateAutoEvBindSiteType ();

	CClassType* 
	CreateISchedulerType ();

	bool
	CreateMulticastCallMethod (CClassType* pMulticastType);
};

//.............................................................................

} // namespace jnc {
} // namespace axl {