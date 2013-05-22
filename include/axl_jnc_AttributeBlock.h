// This file is part of AXL (R) Library
// Tibbo Technology Inc (C) 2004-2013. All rights reserved
// Author: Vladimir Gladkov

#pragma once

#include "axl_jnc_Value.h"
#include "axl_rtl_StringHashTable.h"

namespace axl {
namespace jnc {

//.............................................................................

class CAttribute: public CUserModuleItem
{
protected:
	friend class CAttributeBlock;

	CValue* m_pValue;

public:
	CAttribute ()
	{
		m_pValue = NULL;
	}

	CValue* 
	GetValue ()
	{
		return m_pValue;
	}
};

//.............................................................................

class CAttributeBlock: public CUserModuleItem
{
protected:
	friend class CAttributeMgr;

	CModuleItem* m_pParentItem;

	rtl::CStdListT <CAttribute> m_AttributeList;
	rtl::CStringHashTableMapT <CAttribute*> m_AttributeMap; 

public:
	CAttributeBlock ()
	{
		m_pParentItem = NULL;
	}

	CModuleItem*
	GetParentItem ()
	{
		return m_pParentItem;
	}

	rtl::CConstListT <CAttribute>
	GetAttributeList ()
	{
		return m_AttributeList;
	}

	CAttribute*
	FindAttribute (const char* pName)
	{
		rtl::CStringHashTableMapIteratorT <CAttribute*> It = m_AttributeMap.Find (pName); 
		return It ? It->m_Value : NULL;
	}

	CAttribute*
	CreateAttribute (
		const rtl::CString& Name,
		CValue* pValue = NULL
		);
};

//.............................................................................

} // namespace jnc {
} // namespace axl {
