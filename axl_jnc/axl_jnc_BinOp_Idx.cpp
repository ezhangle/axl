#include "stdafx.h"
#include "axl_jnc_BinOp_Idx.h"
#include "axl_jnc_Module.h"

namespace axl {
namespace jnc {

//.............................................................................

CType*
CBinOp_Idx::GetResultType (
	const CValue& OpValue1,
	const CValue& OpValue2
	)
{
	CType* pOpType1 = OpValue1.GetType ();
	if (pOpType1->GetTypeKind () == EType_DataRef)
	{
		CDataPtrType* pPtrType = (CDataPtrType*) pOpType1;
		CType* pBaseType = pPtrType->GetTargetType ();

		if (pBaseType->GetTypeKind () == EType_Array)
			return ((CArrayType*) pBaseType)->GetElementType ()->GetDataPtrType (
				EType_DataRef, 
				pPtrType->GetPtrTypeKind (), 
				pPtrType->GetFlags ()
				);

		pOpType1 = pBaseType;
	}

	EType TypeKind = pOpType1->GetTypeKind ();
	switch (TypeKind)
	{
	case EType_DataPtr:
		return pOpType1;

	case EType_Array:
		return ((CArrayType*) pOpType1)->GetElementType ();

	case EType_PropertyRef:
	case EType_PropertyPtr:
		return GetPropertyIndexResultType (OpValue1, OpValue2);

	default:
		err::SetFormatStringError (_T("cannot index '%s'"), pOpType1->GetTypeString ());
		return NULL;
	}
}

bool
CBinOp_Idx::Operator (
	const CValue& RawOpValue1,
	const CValue& RawOpValue2,
	CValue* pResultValue
	)
{
	bool Result;

	CValue OpValue1 = RawOpValue1;
	CValue OpValue2 = RawOpValue2;

	CType* pOpType1 = RawOpValue1.GetType ();
	if (pOpType1->GetTypeKind () == EType_DataRef)
	{
		CType* pBaseType = ((CDataPtrType*) pOpType1)->GetTargetType ();

		if (pBaseType->GetTypeKind () == EType_Array)
			return 
				m_pModule->m_OperatorMgr.CastOperator (&OpValue2, EType_Int_p) &&
				ArrayIndexOperator (RawOpValue1, (CArrayType*) pBaseType, OpValue2, pResultValue);

		Result = m_pModule->m_OperatorMgr.LoadDataRef (RawOpValue1, &OpValue1);
		if (!Result)
			return false;

		pOpType1 = OpValue1.GetType ();
	}

	EType TypeKind = pOpType1->GetTypeKind ();
	switch (TypeKind)
	{
	case EType_DataPtr:
		return 
			m_pModule->m_OperatorMgr.CastOperator (&OpValue2, EType_Int_p) &&
			m_pModule->m_OperatorMgr.BinaryOperator (EBinOp_Add, OpValue1, OpValue2, pResultValue);

	case EType_Array:
		return 
			m_pModule->m_OperatorMgr.CastOperator (&OpValue2, EType_Int_p) &&
			ArrayIndexOperator (OpValue1, (CArrayType*) pOpType1, OpValue2, pResultValue);

	case EType_PropertyRef:
	case EType_PropertyPtr:
		return PropertyIndexOperator (OpValue1, OpValue2, pResultValue);

	default:
		err::SetFormatStringError (_T("cannot index '%s'"), pOpType1->GetTypeString ());
		return false;
	}
}

bool
CBinOp_Idx::ArrayIndexOperator (
	const CValue& OpValue1,
	CArrayType* pArrayType,
	const CValue& OpValue2,
	CValue* pResultValue
	)
{
	CType* pElementType = pArrayType->GetElementType ();

	if (OpValue1.GetValueKind () == EValue_Const && OpValue2.GetValueKind ())
	{
		void* p = (char*) OpValue1.GetConstData () + OpValue2.GetSizeT () * pElementType->GetSize ();
		pResultValue->CreateConst (p, pElementType);
		return true;
	}

	EType OpTypeKind1 = OpValue1.GetType ()->GetTypeKind ();

	if (OpTypeKind1 != EType_DataRef)
	{
		ASSERT (OpTypeKind1 == EType_Array);
		err::SetFormatStringError (_T("indexing register-based arrays is not supported yet"));
		return false;
	}

	CDataPtrType* pOpType1 = (CDataPtrType*) OpValue1.GetType ();

	CDataPtrType* pPtrType;
	int PtrTypeFlags = pOpType1->GetFlags () | EPtrTypeFlag_Nullable;
	
	CValue PtrValue;

	EDataPtrType PtrTypeKind = pOpType1->GetPtrTypeKind ();
	switch (PtrTypeKind)
	{
	case EDataPtrType_Unsafe:
		pPtrType = pElementType->GetDataPtrType (EType_DataRef, EDataPtrType_Unsafe, PtrTypeFlags);

		m_pModule->m_LlvmBuilder.CreateGep2 (OpValue1, OpValue2, pPtrType, pResultValue);
		break;

	case EDataPtrType_Thin:
		pPtrType = pElementType->GetDataPtrType (EType_DataRef, EDataPtrType_Thin, PtrTypeFlags);

		m_pModule->m_LlvmBuilder.CreateGep2 (OpValue1, OpValue2, NULL, &PtrValue);

		if (OpValue1.GetValueKind () == EValue_Variable)
			pResultValue->SetThinDataPtr (
				PtrValue.GetLlvmValue (), 
				pPtrType,
				OpValue1
				);
		else
			pResultValue->SetThinDataPtr (
				PtrValue.GetLlvmValue (), 
				pPtrType,
				OpValue1.GetThinDataPtrValidator ()
				);
		break;

	case EDataPtrType_Normal:
		m_pModule->m_LlvmBuilder.CreateExtractValue (OpValue1, 0, NULL, &PtrValue);

		pPtrType = pElementType->GetDataPtrType (EDataPtrType_Unsafe);

		m_pModule->m_LlvmBuilder.CreateGep2 (PtrValue, OpValue2, NULL, &PtrValue);

		pPtrType = pElementType->GetDataPtrType (EType_DataRef, EDataPtrType_Thin, PtrTypeFlags);

		pResultValue->SetThinDataPtr (
			PtrValue.GetLlvmValue (), 
			pPtrType,
			OpValue1
			);

		break;

	default:
		ASSERT (false);
	}

	return true;
}

bool
CBinOp_Idx::PropertyIndexOperator (
	const CValue& RawOpValue1,
	const CValue& RawOpValue2,
	CValue* pResultValue
	)
{
	*pResultValue = RawOpValue1;
	
	CClosure* pClosure = pResultValue->GetClosure ();
	if (!pClosure)
		pClosure = pResultValue->CreateClosure ();

	pClosure->GetArgList ()->InsertTail (RawOpValue2);
	return true;
}

CType*
CBinOp_Idx::GetPropertyIndexResultType (
	const CValue& RawOpValue1,
	const CValue& RawOpValue2
	)
{
	CValue ResultValue;
	PropertyIndexOperator (RawOpValue1, RawOpValue2, &ResultValue);
	return ResultValue.GetClosure ()->GetClosureType (RawOpValue1.GetType ());
}

//.............................................................................

} // namespace jnc {
} // namespace axl {
