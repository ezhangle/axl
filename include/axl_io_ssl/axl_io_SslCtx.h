//..............................................................................
//
//  This file is part of the AXL library.
//
//  AXL is distributed under the MIT license.
//  For details see accompanying license.txt file,
//  the public copy of which is also available at:
//  http://tibbo.com/downloads/archive/axl/license.txt
//
//..............................................................................

#pragma once

#define _AXL_IO_SSLCTX_H

#include "axl_io_SslPch.h"

namespace axl {
namespace io {

//..............................................................................

class FreeSslCtx
{
public:
	void
	operator () (SSL_CTX* h)
	{
		SSL_CTX_free(h);
	}
};

// . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .

typedef
void
SslInfoCallbackFunc(
	const SSL* ssl,
	int type,
	int value
	);

typedef
int
SslVerifyCallbackFunc(
	int isPreVerifyOk,
	X509_STORE_CTX* ctx
	);

// . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .

class SslCtx: public sl::Handle<SSL_CTX*, FreeSslCtx>
{
public:
	bool
	create(const SSL_METHOD* method = SSLv23_method());

	long
	getOptions()
	{
		ASSERT(m_h);
		return ::SSL_CTX_get_options(m_h);
	}

	long
	setOptions(long options)
	{
		ASSERT(m_h);
		return ::SSL_CTX_set_options(m_h, options);
	}

	long
	clearOptions(long options)
	{
		ASSERT(m_h);
		return ::SSL_CTX_clear_options(m_h, options);
	}

	int
	getVerifyDepth()
	{
		ASSERT(m_h);
		return ::SSL_CTX_get_verify_depth(m_h);
	}

	void
	setVerifyDepth(int depth)
	{
		ASSERT(m_h);
		::SSL_CTX_set_verify_depth(m_h, depth);
	}

	void
	setInfoCallback(SslInfoCallbackFunc* callbackFunc)
	{
		ASSERT(m_h);
		::SSL_CTX_set_info_callback(m_h, callbackFunc);
	}

	void
	setVerify(
		int mode,
		SslVerifyCallbackFunc* callbackFunc = NULL
		)
	{
		ASSERT(m_h);
		::SSL_CTX_set_verify(m_h, mode, callbackFunc);
	}

	bool
	loadVerifyLocations(
		const sl::StringRef& caFileName,
		const sl::StringRef& caDir = NULL
		);

	bool
	setCipherList(const sl::StringRef& listString);
};

//..............................................................................

} // namespace io
} // namespace axl