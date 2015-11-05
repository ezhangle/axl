// This file is part of AXL (R) Library
// Tibbo Technology Inc (C) 2004-2015. All rights reserved
// Author: Vladimir Gladkov

#pragma once

#define _AXL_ENC_ESCAPEENCODING_H

#include "axl_enc_HexEncoding.h"

namespace axl {
namespace enc {

//.............................................................................

class EscapeEncoding
{
public:
	static
	char
	findEscapeChar (char x);

	static
	char
	findEscapeReplaceChar (char x);

	static
	size_t
	encode (
		sl::String* string,
		const char* p, 
		size_t length = -1
		);

	static
	sl::String
	encode (
		const char* p, 
		size_t length = -1
		)
	{
		sl::String string;
		encode (&string, p, length);
		return string;
	}

	static
	size_t
	decode (
		sl::String* string,
		const char* p, 
		size_t length = -1
		);

	static
	sl::String
	decode (		
		const char* p, 
		size_t length = -1
		)
	{
		sl::String string;
		decode (&string, p, length);
		return string;
	}
};

//.............................................................................

} // namespace enc
} // namespace axl
