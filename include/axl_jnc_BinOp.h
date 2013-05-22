// This file is part of AXL (R) Library
// Tibbo Technology Inc (C) 2004-2013. All rights reserved
// Author: Vladimir Gladkov

#pragma once

#include "axl_jnc_UnOp.h"

namespace axl {
namespace jnc {

//.............................................................................

enum EBinOp
{
	EBinOp_Undefined = 0,
	
	// arithmetic
	
	EBinOp_Add,
	EBinOp_Sub,
	EBinOp_Mul,
	EBinOp_Div,
	EBinOp_Mod,	
	EBinOp_Shl,
	EBinOp_Shr,	
	EBinOp_BwAnd,
	EBinOp_BwXor,	
	EBinOp_BwOr,

	// special ops

	EBinOp_At,
	EBinOp_Idx,

	// comparison

	EBinOp_Eq,
	EBinOp_Ne,
	EBinOp_Lt,
	EBinOp_Le,
	EBinOp_Gt,
	EBinOp_Ge,

	// logic

	EBinOp_LogAnd,
	EBinOp_LogOr,

	// assignment

	EBinOp_Assign,
	EBinOp_ClassAssign,
	EBinOp_AddAssign,
	EBinOp_SubAssign,
	EBinOp_MulAssign,
	EBinOp_DivAssign,
	EBinOp_ModAssign,
	EBinOp_ShlAssign,
	EBinOp_ShrAssign,
	EBinOp_AndAssign,
	EBinOp_XorAssign,
	EBinOp_OrAssign,
	EBinOp_AtAssign,

	EBinOp__Count,
	EBinOp__OpAssignDelta = EBinOp_AddAssign - EBinOp_Add,
};

//. . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .

const char*
GetBinOpKindString (EBinOp OpKind);

//.............................................................................

struct IBinaryOperator: obj::IRoot
{	
	// {C0A84F09-9553-440D-B8CC-B7E1F27BFFAF}
	AXL_OBJ_INTERFACE (
		IBinaryOperator,
		0xc0a84f09, 0x9553, 0x440d, 0xb8, 0xcc, 0xb7, 0xe1, 0xf2, 0x7b, 0xff, 0xaf
		)

protected:
	friend class COperatorMgr;

	CModule* m_pModule;
	EBinOp m_OpKind;
	int m_OpFlags1;
	int m_OpFlags2;

public:
	IBinaryOperator ();

	CModule*
	GetModule ()
	{
		return m_pModule;
	}

	EBinOp 
	GetOpKind ()
	{
		return m_OpKind;
	}

	int
	GetOpFlags1 ()
	{
		return m_OpFlags1;
	}

	int
	GetOpFlags2 ()
	{
		return m_OpFlags2;
	}

	bool
	GetResultType (
		const CValue& OpValue1,
		const CValue& OpValue2,
		CValue* pResultValue
		);

	virtual
	CType*
	GetResultType (
		const CValue& OpValue1,
		const CValue& OpValue2
		) = 0;

	virtual
	bool
	Operator (
		const CValue& OpValue1,
		const CValue& OpValue2,
		CValue* pResultValue
		) = 0;

	err::CError
	SetOperatorError (		
		CType* pOpType1,
		CType* pOpType2
		)
	{
		return err::SetFormatStringError (
			"binary '%s' cannot be applied to '%s' and '%s'",
			GetBinOpKindString (m_OpKind),
			pOpType1->GetTypeString ().cc (), // thanks a lot gcc
			pOpType2->GetTypeString ().cc ()
			);
	}

	err::CError
	SetOperatorError (		
		const CValue& OpValue1,
		const CValue& OpValue2
		)
	{
		return SetOperatorError (OpValue1.GetType (), OpValue2.GetType ());
	}
};

//.............................................................................

} // namespace jnc {
} // namespace axl {
