// This file is part of AXL (R) Library
// Tibbo Technology Inc (C) 2004-2014. All rights reserved
// Author: Vladimir Gladkov

#pragma once

#define _AXL_CRY_BIGNUM_H

#include "axl_rtl_Handle.h"
#include "axl_rtl_Array.h"
#include "axl_cry_CryptoError.h"

namespace axl {
namespace cry {

//.............................................................................

class FreeBnCtx
{
public:
	void 
	operator () (BN_CTX* h)
	{
		BN_CTX_free (h);
	}
};

//. . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .

class BnCtx: public rtl::Handle <BN_CTX*, FreeBnCtx>
{
public:
	BnCtx ()
	{
	}

	BnCtx (BN_CTX* h):
		rtl::Handle <BN_CTX*, FreeBnCtx> (h)
	{
	}

	void
	start ()
	{
		BN_CTX_start (m_h);
	}

	void
	end ()
	{
		BN_CTX_end (m_h);
	}

	BIGNUM*
	getBigNum ();
};

//.............................................................................

class FreeBigNum
{
public:
	void 
	operator () (BIGNUM* h)
	{
		BN_free (h);
	}
};

//. . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .

class BigNum: public rtl::Handle <BIGNUM*, FreeBigNum>
{
public:
	BigNum ()
	{		
		m_h = NULL;
		create ();
	}

	BigNum (BIGNUM* h):
		rtl::Handle <BIGNUM*, FreeBigNum> (h)
	{
	}

	bool
	create ();

	bool
	createCopy (BIGNUM* src);

	bool
	copy (BIGNUM* src)
	{
		BIGNUM* result = BN_copy (m_h, src);
		return completeWithLastCryptoError (result != NULL);
	}

	size_t 
	getBitCount ()
	{
		return BN_num_bits (m_h);
	}

	size_t 
	getSize ()
	{
		return BN_num_bytes (m_h);
	}
	
	size_t
	getData (
		void* p,
		size_t size
		);

	bool
	getData (rtl::Array <char>* data)
	{
		size_t size = getSize ();
		return data->setCount (size) && getData (*data, size);
	}

	rtl::Array <char>
	getData ()
	{
		rtl::Array <char> data;
		getData (&data);
		return data;
	}

	bool
	setData (
		const void* p,
		size_t size
		)
	{
		BIGNUM* result = BN_bin2bn ((const uchar_t*) p, (int) size, m_h);
		return completeWithLastCryptoError (result != NULL);
	}

	bool
	getDecString (rtl::String* string);

	rtl::String
	getDecString ()
	{
		rtl::String string;
		getDecString (&string);
		return string;
	}

	bool
	setDecString (const char* string)
	{
		int result = BN_dec2bn (&m_h, string);
		return completeWithLastCryptoError (result);
	}

	bool
	getHexString (rtl::String* string);

	rtl::String
	getHexString ()
	{
		rtl::String string;
		getHexString (&string);
		return string;
	}

	bool
	setHexString (const char* string)
	{
		int result = BN_hex2bn (&m_h, string);
		return completeWithLastCryptoError (result);
	}

	bool
	rand (int bitCount)
	{
		int result = BN_rand (m_h, bitCount, -1, 0);
		return completeWithLastCryptoError (result);
	}

	bool
	pseudoRand (int bitCount)
	{
		int result = BN_pseudo_rand (m_h, bitCount, -1, 0);
		return completeWithLastCryptoError (result);
	}
};

//.............................................................................

} // namespace cry
} // namespace axl