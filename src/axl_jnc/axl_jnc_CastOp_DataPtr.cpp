#include "pch.h"
#include "axl_jnc_CastOp_DataPtr.h"
#include "axl_jnc_Module.h"

namespace axl {
namespace jnc {

//.............................................................................

ECast
CCast_DataPtr_FromArray::GetCastKind (
	const CValue& OpValue,
	CType* pType
	)
{
	ASSERT (OpValue.GetType ()->GetTypeKind () == EType_Array);
	ASSERT (pType->GetTypeKind () == EType_DataPtr);

	CArrayType* pSrcType = (CArrayType*) OpValue.GetType ();
	CDataPtrType* pDstType = (CDataPtrType*) pType;

	CType* pArrayElementType = pSrcType->GetElementType ();
	CType* pPtrDataType = pDstType->GetTargetType ();
	
	return 
		pArrayElementType->Cmp (pPtrDataType) == 0 ? ECast_Implicit : 
		(pArrayElementType->GetFlags () & ETypeFlag_Pod) &&
		(pPtrDataType->GetFlags () & ETypeFlag_Pod) ? ECast_Explicit : ECast_None;
}

bool
CCast_DataPtr_FromArray::ConstCast (
	const CValue& OpValue,
	CType* pType,
	void* pDst
	)
{
	ASSERT (OpValue.GetType ()->GetTypeKind () == EType_Array);
	ASSERT (pType->GetTypeKind () == EType_DataPtr);

	CArrayType* pSrcType = (CArrayType*) OpValue.GetType ();
	CDataPtrType* pDstType = (CDataPtrType*) pType;

	const CValue& SavedOpValue = m_pModule->m_ConstMgr.SaveValue (OpValue);
	void* p = SavedOpValue.GetConstData ();

	// #pragma AXL_TODO ("create a global constant holding the array")

	if (pDstType->GetPtrTypeKind () == EDataPtrType_Thin)
	{
		*(void**) pDst = p;
	}
	else
	{
		TDataPtr* pPtr = (TDataPtr*) pDst;
		pPtr->m_p = p;
		pPtr->m_pRangeBegin = p;
		pPtr->m_pRangeEnd = (char*) p + pSrcType->GetSize ();
		pPtr->m_ScopeLevel = 0;
	}

	return true;
}

//.............................................................................

ECast
CCast_DataPtr_Base::GetCastKind (
	const CValue& OpValue,
	CType* pType
	)
{
	ASSERT (OpValue.GetType ()->GetTypeKind () == EType_DataPtr && pType->GetTypeKind () == EType_DataPtr);

	CDataPtrType* pSrcType = (CDataPtrType*) OpValue.GetType ();
	CDataPtrType* pDstType = (CDataPtrType*) pType;

	if (!(pDstType->GetFlags () & EPtrTypeFlag_Unsafe))
	{
		if (pSrcType->IsConstPtrType () && !pDstType->IsConstPtrType ())
			return ECast_None;
	}

	CType* pSrcDataType = pSrcType->GetTargetType ();
	CType* pDstDataType = pDstType->GetTargetType ();

	if (pSrcDataType->Cmp (pDstDataType) == 0)
		return ECast_Implicit;

	if (pSrcDataType->GetTypeKind () != EType_Struct)
		return ECast_Explicit;

	return ((CStructType*) pSrcDataType)->FindBaseTypeTraverse (pDstDataType) ?
		ECast_Implicit :
		ECast_Explicit;
}

intptr_t
CCast_DataPtr_Base::GetOffset (
	CDataPtrType* pSrcType,
	CDataPtrType* pDstType,
	CBaseTypeCoord* pCoord
	)
{	
	CType* pSrcDataType = pSrcType->GetTargetType ();
	CType* pDstDataType = pDstType->GetTargetType ();

	if (pSrcDataType->Cmp (pDstDataType) == 0 ||
		pSrcDataType->GetTypeKind () != EType_Struct ||
		pDstDataType->GetTypeKind () != EType_Struct)
	{
		return 0;
	}

	CStructType* pSrcStructType = (CStructType*) pSrcDataType;
	CStructType* pDstStructType = (CStructType*) pDstDataType;

	if (pSrcStructType->FindBaseTypeTraverse (pDstStructType, pCoord))
		return pCoord->m_Offset;

	CBaseTypeCoord Coord;
	if (pDstStructType->FindBaseTypeTraverse (pSrcStructType, &Coord))
		return -Coord.m_Offset;

	return 0;
}

intptr_t
CCast_DataPtr_Base::GetOffsetUnsafePtrValue (
	const CValue& PtrValue, 
	CDataPtrType* pSrcType,
	CDataPtrType* pDstType,
	CValue* pResultValue
	)
{
	CBaseTypeCoord Coord;
	intptr_t Offset = GetOffset (pSrcType, pDstType, &Coord);

	if (!Coord.m_LlvmIndexArray.IsEmpty ())
	{
		Coord.m_LlvmIndexArray.Insert (0, 0);
		m_pModule->m_LlvmIrBuilder.CreateGep (
			PtrValue, 
			Coord.m_LlvmIndexArray,
			Coord.m_LlvmIndexArray.GetCount (),
			pDstType, 
			pResultValue
			);

		return Offset;
	}

	if (!Offset)
	{
		m_pModule->m_LlvmIrBuilder.CreateBitCast (PtrValue, pDstType, pResultValue);
		return Offset;
	}

	ASSERT (Offset < 0);

	CValue BytePtrValue;
	m_pModule->m_LlvmIrBuilder.CreateBitCast (PtrValue, m_pModule->m_TypeMgr.GetStdType (EStdType_BytePtr), &BytePtrValue);
	m_pModule->m_LlvmIrBuilder.CreateGep (BytePtrValue, (int32_t) Offset, NULL, &BytePtrValue);
	m_pModule->m_LlvmIrBuilder.CreateBitCast (BytePtrValue, pDstType, pResultValue);
	return Offset;
}

//.............................................................................

bool
CCast_DataPtr_Normal2Normal::ConstCast (
	const CValue& OpValue,
	CType* pType,
	void* pDst
	)
{
	ASSERT (OpValue.GetType ()->GetTypeKind () == EType_DataPtr);
	ASSERT (pType->GetTypeKind () == EType_DataPtr);

	intptr_t Offset = GetOffset ((CDataPtrType*) OpValue.GetType (), (CDataPtrType*) pType, NULL);

	TDataPtr* pDstPtr = (TDataPtr*) pDst;
	TDataPtr* pSrcPtr = (TDataPtr*) OpValue.GetConstData ();
	pDstPtr->m_p = (char*) pSrcPtr->m_p + Offset;
	pDstPtr->m_pRangeBegin = pSrcPtr->m_pRangeBegin;
	pDstPtr->m_pRangeEnd = pSrcPtr->m_pRangeEnd;
	pDstPtr->m_ScopeLevel = pSrcPtr->m_ScopeLevel;
	return true;
}

bool
CCast_DataPtr_Normal2Normal::LlvmCast (
	EStorage StorageKind,
	const CValue& OpValue,
	CType* pType,
	CValue* pResultValue
	)
{
	ASSERT (OpValue.GetType ()->GetTypeKind () == EType_DataPtr);
	ASSERT (pType->GetTypeKind () == EType_DataPtr);
	
	if (pType->GetFlags () & EPtrTypeFlag_Checked)
		m_pModule->m_OperatorMgr.CheckDataPtrRange (OpValue);

	CValue PtrValue;
	CValue RangeBeginValue;
	CValue RangeEndValue;
	CValue ScopeLevelValue;

	m_pModule->m_LlvmIrBuilder.CreateExtractValue (OpValue, 0, NULL, &PtrValue);
	m_pModule->m_LlvmIrBuilder.CreateExtractValue (OpValue, 1, NULL, &RangeBeginValue);
	m_pModule->m_LlvmIrBuilder.CreateExtractValue (OpValue, 2, NULL, &RangeEndValue);
	m_pModule->m_LlvmIrBuilder.CreateExtractValue (OpValue, 3, NULL, &ScopeLevelValue);

	CDataPtrType* pUnsafePtrType = ((CDataPtrType*) pType)->GetTargetType ()->GetDataPtrType_c ();
	GetOffsetUnsafePtrValue (PtrValue, (CDataPtrType*) OpValue.GetType (), pUnsafePtrType, &PtrValue);

	CLlvmScopeComment Comment (&m_pModule->m_LlvmIrBuilder, "create safe data pointer");

	CValue ResultValue = pType->GetUndefValue ();
	m_pModule->m_LlvmIrBuilder.CreateInsertValue (ResultValue, PtrValue, 0, NULL, &ResultValue);
	m_pModule->m_LlvmIrBuilder.CreateInsertValue (ResultValue, RangeBeginValue, 1, NULL, &ResultValue);
	m_pModule->m_LlvmIrBuilder.CreateInsertValue (ResultValue, RangeEndValue, 2, NULL, &ResultValue);
	m_pModule->m_LlvmIrBuilder.CreateInsertValue (ResultValue, ScopeLevelValue, 3, pType, pResultValue);
	return true;
}

//. . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .

bool
CCast_DataPtr_Thin2Normal::ConstCast (
	const CValue& OpValue,
	CType* pType,
	void* pDst
	)
{
	ASSERT (OpValue.GetType ()->GetTypeKind () == EType_DataPtr);
	ASSERT (pType->GetTypeKind () == EType_DataPtr);

	EDataPtrType SrcPtrTypeKind = ((CDataPtrType*) OpValue.GetType ())->GetPtrTypeKind ();
	ASSERT (SrcPtrTypeKind == EDataPtrType_Thin);

	intptr_t Offset = GetOffset ((CDataPtrType*) OpValue.GetType (), (CDataPtrType*) pType, NULL);

	TDataPtr* pDstPtr = (TDataPtr*) pDst;
	const void* pSrc = OpValue.GetConstData ();
	pDstPtr->m_p = (char*) pSrc + Offset;
	pDstPtr->m_pRangeBegin = NULL;
	pDstPtr->m_pRangeEnd = (void*) -1;
	pDstPtr->m_ScopeLevel = 0;

	return true;
}

bool
CCast_DataPtr_Thin2Normal::LlvmCast (
	EStorage StorageKind,
	const CValue& OpValue,
	CType* pType,
	CValue* pResultValue
	)
{
	ASSERT (OpValue.GetType ()->GetTypeKind () == EType_DataPtr);
	ASSERT (pType->GetTypeKind () == EType_DataPtr);

	EDataPtrType SrcPtrTypeKind = ((CDataPtrType*) OpValue.GetType ())->GetPtrTypeKind ();
	ASSERT (SrcPtrTypeKind == EDataPtrType_Thin);

	CValue PtrValue;
	CDataPtrType* pUnsafePtrType = ((CDataPtrType*) pType)->GetTargetType ()->GetDataPtrType_c ();
	GetOffsetUnsafePtrValue (OpValue, (CDataPtrType*) OpValue.GetType (), pUnsafePtrType, &PtrValue);

	if (SrcPtrTypeKind == EDataPtrType_Thin)
	{
		CValue RangeBeginValue;
		CValue RangeEndValue;
		CValue ScopeLevelValue;

		m_pModule->m_OperatorMgr.GetThinDataPtrRange (OpValue, &RangeBeginValue, &RangeEndValue);

		if (pType->GetFlags () & EPtrTypeFlag_Checked)
			m_pModule->m_OperatorMgr.CheckDataPtrRange (OpValue);

		m_pModule->m_OperatorMgr.GetThinDataPtrScopeLevel (OpValue, &ScopeLevelValue);

		CLlvmScopeComment Comment (&m_pModule->m_LlvmIrBuilder, "create safe data pointer");

		CValue ResultValue = pType->GetUndefValue ();
		m_pModule->m_LlvmIrBuilder.CreateInsertValue (ResultValue, PtrValue, 0, NULL, &ResultValue);
		m_pModule->m_LlvmIrBuilder.CreateInsertValue (ResultValue, RangeBeginValue, 1, NULL, &ResultValue);
		m_pModule->m_LlvmIrBuilder.CreateInsertValue (ResultValue, RangeEndValue, 2, NULL, &ResultValue);
		m_pModule->m_LlvmIrBuilder.CreateInsertValue (ResultValue, ScopeLevelValue, 3, pType, pResultValue);
	}
	else
	{
		CType* pBytePtrType = m_pModule->GetSimpleType (EStdType_BytePtr);

		void* pRangeBegin = NULL;
		void* pRangeEnd = (void*) -1;

		CValue RangeBeginValue (&pRangeBegin, pBytePtrType);
		CValue RangeEndValue (&pRangeEnd, pBytePtrType);
		CValue ScopeLevelValue ((int64_t) 0, EType_SizeT);

		CLlvmScopeComment Comment (&m_pModule->m_LlvmIrBuilder, "create safe data pointer");

		CValue ResultValue = pType->GetUndefValue ();
		m_pModule->m_LlvmIrBuilder.CreateInsertValue (ResultValue, PtrValue, 0, NULL, &ResultValue);
		m_pModule->m_LlvmIrBuilder.CreateInsertValue (ResultValue, RangeBeginValue, 1, NULL, &ResultValue);
		m_pModule->m_LlvmIrBuilder.CreateInsertValue (ResultValue, RangeEndValue, 2, NULL, &ResultValue);
		m_pModule->m_LlvmIrBuilder.CreateInsertValue (ResultValue, ScopeLevelValue, 3, pType, pResultValue);
	}

	return true;
}

//. . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .

bool
CCast_DataPtr_Normal2Thin::ConstCast (
	const CValue& OpValue,
	CType* pType,
	void* pDst
	)
{
	ASSERT (OpValue.GetType ()->GetTypeKind () == EType_DataPtr);
	ASSERT (pType->GetTypeKind () == EType_DataPtr);

	intptr_t Offset = GetOffset ((CDataPtrType*) OpValue.GetType (), (CDataPtrType*) pType, NULL);
	*(char**) pDst = *(char**) OpValue.GetConstData () + Offset;
	return true;
}

bool
CCast_DataPtr_Normal2Thin::LlvmCast (
	EStorage StorageKind,
	const CValue& OpValue,
	CType* pType,
	CValue* pResultValue
	)
{
	ASSERT (OpValue.GetType ()->GetTypeKind () == EType_DataPtr);
	ASSERT (pType->GetTypeKind () == EType_DataPtr);

	CValue PtrValue;
	m_pModule->m_LlvmIrBuilder.CreateExtractValue (OpValue, 0, NULL, &PtrValue);
	GetOffsetUnsafePtrValue (PtrValue, (CDataPtrType*) OpValue.GetType (), (CDataPtrType*) pType, pResultValue);
	return true;
}

//. . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .

bool
CCast_DataPtr_Thin2Thin::ConstCast (
	const CValue& OpValue,
	CType* pType,
	void* pDst
	)
{
	ASSERT (OpValue.GetType ()->GetTypeKind () == EType_DataPtr);
	ASSERT (pType->GetTypeKind () == EType_DataPtr);

	intptr_t Offset = GetOffset ((CDataPtrType*) OpValue.GetType (), (CDataPtrType*) pType, NULL);
	*(char**) pDst = *(char**) OpValue.GetConstData () + Offset;
	return true;
}

bool
CCast_DataPtr_Thin2Thin::LlvmCast (
	EStorage StorageKind,
	const CValue& OpValue,
	CType* pType,
	CValue* pResultValue
	)
{
	ASSERT (OpValue.GetType ()->GetTypeKind () == EType_DataPtr);
	ASSERT (pType->GetTypeKind () == EType_DataPtr);

	GetOffsetUnsafePtrValue (OpValue, (CDataPtrType*) OpValue.GetType (), (CDataPtrType*) pType, pResultValue);
	return true;
}

//.............................................................................

CCast_DataPtr::CCast_DataPtr ()
{
	memset (m_OperatorTable, 0, sizeof (m_OperatorTable));

	m_OperatorTable [EDataPtrType_Normal] [EDataPtrType_Normal] = &m_Normal2Normal;
	m_OperatorTable [EDataPtrType_Normal] [EDataPtrType_Thin]   = &m_Normal2Thin;
	m_OperatorTable [EDataPtrType_Thin] [EDataPtrType_Normal]   = &m_Thin2Normal;
	m_OperatorTable [EDataPtrType_Thin] [EDataPtrType_Thin]     = &m_Thin2Thin;
}

ICastOperator*
CCast_DataPtr::GetCastOperator (
	const CValue& OpValue,
	CType* pType
	)
{
	ASSERT (pType->GetTypeKind () == EType_DataPtr);
	
	CDataPtrType* pDstPtrType = (CDataPtrType*) pType;
	EDataPtrType DstPtrTypeKind = pDstPtrType->GetPtrTypeKind ();

	CType* pSrcType = OpValue.GetType ();

	if (pSrcType->GetTypeKindFlags () & ETypeKindFlag_Integer)
	{
		return DstPtrTypeKind == EDataPtrType_Thin && (pType->GetFlags () & EPtrTypeFlag_Unsafe) ? 
			m_pModule->m_OperatorMgr.GetStdCastOperator (EStdCast_PtrFromInt) : 
			NULL;
	}
	else if (pSrcType->GetTypeKind () == EType_Array)
	{
		return &m_FromArray;
	}
	else if (pSrcType->GetTypeKind () != EType_DataPtr)
	{
		return NULL;
	}
		
	CDataPtrType* pSrcPtrType = (CDataPtrType*) pSrcType;
	EDataPtrType SrcPtrTypeKind = pSrcPtrType->GetPtrTypeKind ();

	if (DstPtrTypeKind == EDataPtrType_Normal &&
		(pSrcPtrType->GetTargetType ()->GetFlags () & ETypeFlag_Pod) != 
		(pDstPtrType->GetTargetType ()->GetFlags () & ETypeFlag_Pod))
	{
		return NULL;
	}

	ASSERT ((size_t) SrcPtrTypeKind < EDataPtrType__Count);
	ASSERT ((size_t) DstPtrTypeKind < EDataPtrType__Count);

	return m_OperatorTable [SrcPtrTypeKind] [DstPtrTypeKind];
}

//.............................................................................

ECast
CCast_DataRef::GetCastKind (
	const CValue& OpValue,
	CType* pType
	)
{
	ASSERT (pType->GetTypeKind () == EType_DataRef);

	CType* pIntermediateSrcType = m_pModule->m_OperatorMgr.GetUnaryOperatorResultType (EUnOp_Addr, OpValue);
	if (!pIntermediateSrcType)
		return ECast_None;

	CDataPtrType* pPtrType = (CDataPtrType*) pType;
	CDataPtrType* pIntermediateDstType = pPtrType->GetTargetType ()->GetDataPtrType (
		EType_DataPtr,
		pPtrType->GetPtrTypeKind (),
		pPtrType->GetFlags ()
		);

	return m_pModule->m_OperatorMgr.GetCastKind (pIntermediateSrcType, pIntermediateDstType);
}

bool
CCast_DataRef::LlvmCast (
	EStorage StorageKind,
	const CValue& OpValue,
	CType* pType,
	CValue* pResultValue
	)
{
	ASSERT (pType->GetTypeKind () == EType_DataRef);
	
	CDataPtrType* pPtrType = (CDataPtrType*) pType;
	CDataPtrType* pIntermediateType = pPtrType->GetTargetType ()->GetDataPtrType (
		EType_DataPtr,
		pPtrType->GetPtrTypeKind (),
		pPtrType->GetFlags ()
		);

	CValue IntermediateValue;

	return
		m_pModule->m_OperatorMgr.UnaryOperator (EUnOp_Addr, OpValue, &IntermediateValue) &&
		m_pModule->m_OperatorMgr.CastOperator (&IntermediateValue, pIntermediateType) &&
		m_pModule->m_OperatorMgr.UnaryOperator (EUnOp_Indir, IntermediateValue, pResultValue);
}

//.............................................................................

} // namespace jnc {
} // namespace axl {
