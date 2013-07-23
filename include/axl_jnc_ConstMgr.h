// This file is part of AXL (R) Library
// Tibbo Technology Inc (C) 2004-2013. All rights reserved
// Author: Vladimir Gladkov

#pragma once

#include "axl_jnc_Value.h"
#include "axl_jnc_ThinDataPtrValidator.h"

namespace axl {
namespace jnc {

//.............................................................................

class CConstMgr
{
	friend class CModule;

protected:
	CModule* m_pModule;

	ref::CPtrT <CThinDataPtrValidator> m_UnsafeThinDataPtrValidator;
	rtl::CBoxListT <CValue> m_ConstList;

public:
	CConstMgr ();

	CModule* 
	GetModule ()
	{
		return m_pModule;
	}

	void
	Clear ();

	const CValue& 
	SaveValue (const CValue& Value)
	{
		rtl::CBoxIteratorT <CValue> It = m_ConstList.InsertTail (Value);
		return *It;
	}

	const CValue& 
	SaveLiteral (
		const char* p,
		size_t Length = -1
		);

	CThinDataPtrValidator*
	GetUnsafeThinDataPtrValidator ();
};

//.............................................................................

} // namespace jnc {
} // namespace axl {
