// This file is part of AXL (R) Library
// Tibbo Technology Inc (C) 2004-2015. All rights reserved
// Author: Vladimir Gladkov

#pragma once

#define _AXL_XML_ERROR_H

#include "axl_err_Error.h"
#include "axl_err_ErrorMgr.h"
#include "axl_sl_String.h"

namespace axl {
namespace xml {

//.............................................................................

// {034B6D20-64F7-4EC1-8C5F-B23F146C8765}
AXL_SL_DEFINE_GUID (
	g_expatErrorGuid,
	0x34b6d20, 0x64f7, 0x4ec1, 0x8c, 0x5f, 0xb2, 0x3f, 0x14, 0x6c, 0x87, 0x65
	);

//.............................................................................

class ExpatErrorProvider: public err::ErrorProvider
{
public:
	static
	sl::String 
	getErrorDescription (XML_Error code)
	{
		const XML_LChar* string = XML_ErrorString (code);
		return string ? sl::String (string) : "undefined XML error";
	}

	virtual 
	sl::String 
	getErrorDescription (const err::ErrorHdr* error)
	{
		return getErrorDescription ((XML_Error) error->m_code);
	}
};

//. . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .

inline 
void 
registerExpatErrorProvider ()
{
	err::getErrorMgr ()->registerProvider (
		g_expatErrorGuid, 
		sl::getSimpleSingleton <ExpatErrorProvider> ()
		);
}

//.............................................................................

class ExpatError: public err::Error
{
public:
	ExpatError ()
	{
	}

	ExpatError (XML_Error code)
	{
		create (code);
	}

	err::ErrorHdr* 
	create (XML_Error code);
};

//.............................................................................

inline
err::Error
setExpatError (XML_Error code)
{
	setError (ExpatError (code));
}

//.............................................................................

} // namespace xml
} // namespace axl