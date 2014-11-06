// This file is part of AXL (R) Library
// Tibbo Technology Inc (C) 2004-2014. All rights reserved
// Author: Vladimir Gladkov

#pragma once

#define _AXL_ENC_HEXENCODING_H

#include "axl_rtl_String.h"
#include "axl_rtl_Array.h"

namespace axl {
namespace enc {

//.............................................................................

class HexEncoding
{
public:
	enum Flag
	{
		Flag_UpperCase = 1,
		Flag_NoSpace   = 2,
	};

public:
	static 
	char
	getHexChar_l (uchar_t x)
	{
		static char charTable [] = "0123456789abcdef";
		return charTable [x & 0xf];
	}

	static 
	char
	getHexChar_u (uchar_t x)
	{
		static char charTable [] = "0123456789ABCDEF";	
		return charTable [x & 0xf];
	}

	static 
	uchar_t
	getHexCharValue (char x)
	{
		return 
			x >= '0' && x <= '9' ? x - '0' :
			x >= 'a' && x <= 'f' ? 10 + x - 'a' :
			x >= 'A' && x <= 'F' ? 10 + x - 'A' : 0;
	}

	static
	size_t
	encode (
		rtl::String* string,
		const void* p, 
		size_t size,
		uint_t flags = 0
		);

	static
	rtl::String
	encode (
		const void* p, 
		size_t size,
		uint_t flags = 0
		)
	{
		rtl::String string;
		encode (&string, p, size, flags);
		return string;
	}

	static
	size_t
	decode (
		rtl::Array <uchar_t>* buffer,
		const char* p, 
		size_t length = -1
		);

	static
	rtl::Array <uchar_t>
	decode (
		const char* p, 
		size_t length = -1
		)
	{
		rtl::Array <uchar_t> buffer;
		decode (&buffer, p, length);
		return buffer;
	}

	static
	size_t
	decode (
		rtl::Array <uchar_t>* buffer,
		const rtl::String& string
		)
	{
		return decode (buffer, string, string.getLength ());
	}

	static
	rtl::Array <uchar_t>
	decode (const rtl::String& string)
	{
		return decode (string, string.getLength ());
	}

protected:
	static
	void
	encode_l (
		char* dst,
		const uchar_t* src, 
		const uchar_t* srcEnd
		);

	static
	void
	encode_u (
		char* dst,
		const uchar_t* src, 
		const uchar_t* srcEnd
		);

	static
	void
	encode_nsl (
		char* dst,
		const uchar_t* src, 
		const uchar_t* srcEnd
		);

	static
	void
	encode_nsu (
		char* dst,
		const uchar_t* src, 
		const uchar_t* srcEnd
		);
};

//.............................................................................

} // namespace enc
} // namespace axl