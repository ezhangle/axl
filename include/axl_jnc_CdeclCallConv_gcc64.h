// This file is part of AXL (R) Library
// Tibbo Technology Inc (C) 2004-2013. All rights reserved
// Author: Vladimir Gladkov

#pragma once

#define _AXL_JNC_CDECLCALLCONV_GCC64

#include "axl_jnc_CallConv.h"

namespace axl {
namespace jnc {

//.............................................................................

class CCdeclCallConv_gcc64: public CCallConv
{
public:
	CCdeclCallConv_gcc64 ()
	{
		m_CallConvKind = ECallConv_Cdecl_gcc64;
	}

	virtual
	llvm::FunctionType*
	GetLlvmFunctionType (CFunctionType* pFunctionType);

	virtual
	llvm::Function*
	CreateLlvmFunction (
		CFunctionType* pFunctionType,
		const char* pTag
		);

	virtual
	void
	Call (
		const CValue& CalleeValue,
		CFunctionType* pFunctionType,
		rtl::CBoxListT <CValue>* pArgValueList,
		CValue* pResultValue
		);

	virtual
	void
	Return (
		CFunction* pFunction,
		const CValue& Value
		);

	virtual
	CValue
	GetThisArgValue (CFunction* pFunction);

	virtual
	void
	CreateArgVariables (CFunction* pFunction);
};

//.............................................................................

} // namespace jnc {
} // namespace axl {
