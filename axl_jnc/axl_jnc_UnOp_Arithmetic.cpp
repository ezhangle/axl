#include "stdafx.h"
#include "axl_jnc_UnOp_Arithmetic.h"
#include "axl_jnc_Module.h"

namespace axl {
namespace jnc {

//.............................................................................

CType*
GetArithmeticOperatorResultTypeKind (CType* pOpType)
{
	EType TypeKind = pOpType->GetTypeKind ();

	switch (TypeKind)
	{
	case EType_Int8:
	case EType_Int16:
	case EType_Int16_be:
	case EType_Int32_be:
		TypeKind = EType_Int32;
		break;

	case EType_Int8_u:
	case EType_Int16_u:
	case EType_Int16_beu:
	case EType_Int32_beu:
		TypeKind = EType_Int32_u;
		break;
	
	case EType_Int64_be:
		TypeKind = EType_Int64;
		break;

	case EType_Int64_beu:
		TypeKind = EType_Int64_u;
		break;

	case EType_Int32:
	case EType_Int32_u:
	case EType_Int64:
	case EType_Int64_u:
	case EType_Float:
	case EType_Double:
		// no change
		break;

	default:
		return NULL;
	}

	return pOpType->GetModule ()->m_TypeMgr.GetPrimitiveType (TypeKind);
}

//.............................................................................

llvm::Value*
CUnOp_Minus::LlvmOpInt (
	CModule* pModule,
	const CValue& OpValue,
	CType* pResultType,
	CValue* pResultValue
	)
{
	return pModule->m_LlvmBuilder.CreateNeg_i (OpValue, pResultType, pResultValue);
}

llvm::Value*
CUnOp_Minus::LlvmOpFp (
	CModule* pModule,
	const CValue& OpValue,
	CType* pResultType,
	CValue* pResultValue
	)
{
	return pModule->m_LlvmBuilder.CreateNeg_f (OpValue, pResultType, pResultValue);
}

//.............................................................................

llvm::Value*
CUnOp_BwNot::LlvmOpInt (
	CModule* pModule,
	const CValue& OpValue,
	CType* pResultType,
	CValue* pResultValue
	)
{
	return pModule->m_LlvmBuilder.CreateNot (OpValue, pResultType, pResultValue);
}

//.............................................................................

} // namespace jnc {
} // namespace axl {