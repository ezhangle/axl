// This file is part of AXL (R) Library
// Tibbo Technology Inc (C) 2004-2013. All rights reserved
// Author: Vladimir Gladkov

#pragma once

#include "axl_jnc_BinOp.h"

namespace axl {
namespace jnc {

//.............................................................................

class CBinOp_At: public IBinaryOperator
{
public:
	CBinOp_At ()
	{
		m_OpKind = EBinOp_At;
	}

	virtual
	CType*
	GetResultType (
		const CValue& OpValue1,
		const CValue& OpValue2
		);

	virtual
	bool
	Operator (
		const CValue& RawOpValue1,
		const CValue& RawOpValue2,
		CValue* pResultValue
		);
};

//.............................................................................

} // namespace jnc {
} // namespace axl {
