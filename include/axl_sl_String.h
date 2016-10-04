// This file is part of AXL (R) Library
// Tibbo Technology Inc (C) 2004-2015. All rights reserved
// Author: Vladimir Gladkov

#pragma once

#define _AXL_SL_STRING_H

#include "axl_sl_StringDetails.h"
#include "axl_ref_Buf.h"

namespace axl {
namespace sl {

template <typename T, typename Details> class StringBase;

//.............................................................................

template <
	typename T,
	typename Details0 = StringDetailsBase <T>
	>
class StringRefBase
{
public:
	typedef Details0 Details;
	typedef typename Details::Details2 Details2;
	typedef typename Details::Details3 Details3;

	typedef typename Details::C C;
	typedef typename Details::C2 C2;
	typedef typename Details::C3 C3;

	typedef typename Details::Encoding Encoding;
	typedef typename Details2::Encoding Encoding2;
	typedef typename Details3::Encoding Encoding3;

	typedef StringRefBase <C, Details> StringRef;
	typedef StringRefBase <C2, Details2> StringRef2;
	typedef StringRefBase <C3, Details3> StringRef3;

	typedef StringBase <C, Details> String;
	typedef StringBase <C2, Details2> String2;
	typedef StringBase <C3, Details3> String3;

protected:
	mutable C* m_p;
	mutable ref::BufHdr* m_hdr;

#if (AXL_PTR_BITS == 64)
	size_t m_length : 63;
#else
	size_t m_length : 31; // more than enough
#endif

	mutable size_t m_isNullTerminated : 1;

public:
	StringRefBase ()
	{
		initialize ();
	}

	StringRefBase (const StringRef& src)
	{
		initialize ();
		attach (src);
	}

	StringRefBase (const C* p)
	{
		initialize ();
		attach (NULL, p, Details::calcLength (p), true);
	}

	StringRefBase (
		const C* p,
		size_t length
		)
	{
		initialize ();
		attach (NULL, p, length, false);
	}

	StringRefBase (
		const C* p,
		const void* end
		)
	{
		initialize ();
		attach (NULL, p, (C*) end - p, false);
	}

	StringRefBase (
		ref::BufHdr* hdr,
		const C* p
		)
	{
		initialize ();
		attach (hdr, p, Details::calcLength (p), true);
	}

	StringRefBase (
		ref::BufHdr* hdr,
		const C* p,
		size_t length
		)
	{
		initialize ();
		attach (hdr, p, length, false);
	}

	StringRefBase (
		ref::BufHdr* hdr,
		const C* p,
		const void* end
		)
	{
		initialize ();
		attach (hdr, p, (C*) end - p, false);
	}

	~StringRefBase ()
	{
		release ();
	}

	StringRefBase&
	operator = (const StringRef& src)
	{
		attach (src);
		return *this;
	}

	bool
	operator == (const StringRef& string) const
	{
		return cmp (string) == 0;
	}

	bool
	operator != (const StringRef& string) const
	{
		return cmp (string) != 0;
	}

	bool
	operator < (const StringRef& string) const
	{
		return cmp (string) < 0;
	}

	bool
	operator <= (const StringRef& string) const
	{
		return cmp (string) <= 0;
	}

	bool
	operator > (const StringRef& string) const
	{
		return cmp (string) > 0;
	}

	bool
	operator >= (const StringRef& string) const
	{
		return cmp (string) >= 0;
	}

	bool
	operator == (const C* p) const
	{
		return cmp (p) == 0;
	}

	bool
	operator != (const C* p) const
	{
		return cmp (p) != 0;
	}

	bool
	operator < (const C* p) const
	{
		return cmp (p) < 0;
	}

	bool
	operator <= (const C* p) const
	{
		return cmp (p) <= 0;
	}

	bool
	operator > (const C* p) const
	{
		return cmp (p) > 0;
	}

	bool
	operator >= (const C* p) const
	{
		return cmp (p) >= 0;
	}

	StringRefBase
	operator + (const StringRef& string) const
	{
		String result = *this;
		result.append (string);
		return result;
	}

	StringRefBase
	operator + (const StringRef2& string) const
	{
		String result = *this;
		result.append (string);
		return result;
	}

	StringRefBase
	operator + (const StringRef3& string) const
	{
		String result = *this;
		result.append (string);
		return result;
	}

	StringRefBase
	operator + (const C* p) const
	{
		String result = *this;
		result.append (p);
		return result;
	}

	StringRefBase
	operator + (const C2* p) const
	{
		String result = *this;
		result.append (p);
		return result;
	}

	StringRefBase
	operator + (const C3* p) const
	{
		String result = *this;
		result.append (p);
		return result;
	}

	const C&
	operator [] (intptr_t i) const
	{
		ASSERT ((size_t) i < m_length);
		return m_p [(size_t) i];
	}

	const C*
	cp () const
	{
		return m_p;
	}

	const C*
	sz () const
	{
		return m_length ? ensureNullTerminated () : Details::getEmptyString ();
	}

	const C*
	szn () const
	{
		return m_length ? ensureNullTerminated () : NULL;
	}

	StringRef2
	s2 () const
	{
		return String2 (m_p, m_length);
	}

	StringRef3
	s3 () const
	{
		return String3 (m_p, m_length);
	}

	size_t
	getLength () const
	{
		return m_length;
	}

	ref::BufHdr* 
	getHdr () const
	{
		return m_hdr;
	}

	const C* 
	getEnd () const
	{
		return m_p + m_length;
	}


	bool
	isEmpty () const
	{
		return m_length == 0;
	}

	bool
	isNullTerminated () const
	{
		return m_isNullTerminated;
	}

	void
	clear ()
	{
		release ();
	}

	void
	release ()
	{
		if (m_hdr)
			m_hdr->release ();

		initialize ();
	}

	size_t
	offset (size_t length)
	{
		if (length > m_length)
			length = m_length;

		m_p += length;
		m_length -= length;
		return m_length;
	}

	int
	cmp (const StringRef& string) const
	{
		int result = Details::cmp (m_p, string.m_p, AXL_MIN (m_length, string.m_length));
		return 
			result ? result : 
			m_length < string.m_length ? -1 : 
			m_length > string.m_length ? 1 : 0;
	}

	size_t
	hash () const
	{
		return djb2 (m_p, m_length * sizeof (C));
	}

	bool
	isEqual (const StringRef& string) const
	{
		return 
			m_length == string.m_length &&
			Details::cmp (m_p, string.m_p, m_length) == 0;
	}

	bool
	isPrefix (const StringRef& string) const
	{
		return 
			m_length >= string.m_length && 
			Details::cmp (m_p, string.m_p, string.m_length) == 0;
	}

	bool
	isSuffix (const StringRef& string) const
	{
		return 
			m_length >= string.m_length && 
			Details::cmp (m_p + m_length - string.m_length, string.m_p, string.m_length) == 0;
	}

	size_t 
	find (C c) const
	{
		return Details::find (m_p, m_length, c);
	}

	size_t 
	find (const StringRef& subString) const
	{
		return Details::find (m_p, m_length, subString.m_p, subString.m_length);
	}

	size_t 
	findOneOf (const StringRef& charSet) const
	{
		return Details::findOneOf (m_p, m_length, charSet.m_p, charSet.m_length);
	}

	size_t 
	findNotOneOf (const StringRef& charSet) const
	{
		return Details::findNotOneOf (m_p, m_length, charSet.m_p, charSet.m_length);
	}

	size_t 
	reverseFind (C c) const
	{
		return Details::reverseFind (m_p, m_length, c);
	}

	size_t 
	reverseFind (const StringRef& subString) const
	{
		return Details::reverseFind (m_p, m_length, subString.m_p, subString.m_length);
	}

	size_t 
	reverseFindOneOf (const StringRef& charSet) const
	{
		return Details::reverseFindOneOf (m_p, m_length, charSet.m_p, charSet.m_length);
	}

	size_t 
	reverseFindNotOneOf (const StringRef& charSet) const
	{
		return Details::reverseFindNotOneOf (m_p, m_length, charSet.m_p, charSet.m_length);
	}

	StringRef
	getSubString (
		size_t first,
		size_t length = -1
		) const
	{
		if (first > m_length)
			return StringRef ();

		size_t end = length == -1 ? m_length : first + length;
		if (end > m_length)
			end = m_length;
	
		return StringRef (m_hdr, m_p + first, end - first);
	}

	StringRef
	getLeftSubString (size_t length) const
	{
		if (length > m_length)
			return length;

		return StringRef (m_hdr, m_p, length);
	}

	StringRef
	getRightSubString (size_t length) const
	{
		if (length > m_length)
			return length;

		return StringRef (m_hdr, m_p + m_length - length, length);
	}

	StringRef
	getLeftTrimmedString () const
	{
		String string = *this;
		string.trimLeft ();
		return string;
	}

	StringRef
	getRightTimmedString () const
	{
		String string = *this;
		string.trimRight ();
		return string;
	}

	StringRef
	getTrimmedString () const
	{
		String string = *this;
		string.trim ();
		return string;
	}

	StringRef
	getLowerCaseString ()
	{
		String string = *this;
		string.makeLowerCase ();
		return string;
	}

	StringRef
	getUpperCaseString ()
	{
		String string = *this;
		string.makeUpperCase ();
		return string;
	}

	StringRef
	getCaseFoldedString ()
	{
		String string = *this;
		string.makeCaseFolded ();
		return string;
	}

protected:
	const C*
	ensureNullTerminated () const
	{
		if (m_isNullTerminated)
			return m_p;

		if (m_hdr && m_hdr->isInsideBuffer (m_p + m_length) && !m_p [m_length])
		{
			m_isNullTerminated = true;
			return m_p;
		}

		String string (*this);
		attachBufHdr (string.getHdr ());
		m_p = (C*) string.sz ();
		m_isNullTerminated = true;
		return m_p;
	}

	void
	initialize ()
	{
		m_p = NULL;
		m_hdr = NULL;
		m_length = 0;
		m_isNullTerminated = false;
	}

	void
	attachBufHdr (ref::BufHdr* hdr) const
	{
		if (hdr == m_hdr)
			return; // try to avoid unnecessary interlocked ops

		if (hdr)
			hdr->addRef ();

		if (m_hdr)
			m_hdr->release ();
		
		m_hdr = hdr;
	}

	void
	attach (const StringRef& src)
	{
		if (&src != this)
			attach (src.m_hdr, src.m_p, src.m_length, src.m_isNullTerminated);
	}

	void
	attach (
		ref::BufHdr* hdr,
		const C* p,
		size_t length,
		bool isNullTerminated
		)
	{
		attachBufHdr (hdr);

		m_p = (C*) p;
		m_length = length;
		m_isNullTerminated = isNullTerminated;
	}
};

//.............................................................................

template <
	typename T,
	typename Details0 = StringDetailsBase <T>
	>
class StringBase: public StringRefBase <T, Details0>
{
public:
	typedef StringRefBase <T, Details0> StringRef;

	typedef typename StringRef::Details Details;
	typedef typename StringRef::Details2 Details2;
	typedef typename StringRef::Details3 Details3;

	typedef typename StringRef::C C;
	typedef typename StringRef::C2 C2;
	typedef typename StringRef::C3 C3;

	typedef typename StringRef::Encoding Encoding;
	typedef typename StringRef::Encoding2 Encoding2;
	typedef typename StringRef::Encoding3 Encoding3;

	typedef typename StringRef::StringRef2 StringRef2;
	typedef typename StringRef::StringRef3 StringRef3;
	
public:
	StringBase ()
	{
	}

	StringBase (const StringBase& src)
	{
		copy (src);
	}

	StringBase (const StringRef& src)
	{
		copy (src);
	}

	StringBase (const StringRef2& src)
	{
		copy (src);
	}

	StringBase (const StringRef3& src)
	{
		copy (src);
	}

	StringBase (
		const C* p,
		size_t length = -1
		)
	{
		copy (p, length);
	}

	StringBase (
		const C* p,
		const void* end
		)
	{
		copy (p, (C*) end - p);
	}

	StringBase (
		const C2* p,
		size_t length = -1
		)
	{
		copy (p, length);
	}

	StringBase (
		const C2* p,
		const void* end
		)
	{
		copy (p, (C2*) end - p);
	}

	StringBase (
		const C3* p,
		size_t length = -1
		)
	{
		copy (p, length);
	}

	StringBase (
		const C3* p,
		const void* end
		)
	{
		copy (p, (C3*) end - p);
	}

	StringBase (utf32_t x)
	{
		copy (x);
	}

	StringBase (
		utf32_t x,
		size_t count
		)
	{
		copy (x, count);
	}

	StringBase (
		ref::BufKind kind,
		void* p,
		size_t size
		)
	{
		setBuffer (kind, p, size);
	}

	operator const C* () const
	{
		return sz ();
	}

	StringBase&
	operator = (const StringBase& src)
	{
		copy (src);
		return *this;
	}

	StringBase&
	operator = (const StringRef& src)
	{
		copy (src);
		return *this;
	}

	StringBase&
	operator = (const StringRef2& src)
	{
		copy (src);
		return *this;
	}

	StringBase&
	operator = (const StringRef3& src)
	{
		copy (src);
		return *this;
	}

	StringBase&
	operator = (const C* p)
	{
		copy (p, -1);
		return *this;
	}

	StringBase&
	operator = (const C2* p)
	{
		copy (p, -1);
		return *this;
	}

	StringBase&
	operator = (const C3* p)
	{
		copy (p, -1);
		return *this;
	}

	StringBase&
	operator = (utf32_t x)
	{
		copy (x);
		return *this;
	}

	StringBase&
	operator += (const StringRef& string)
	{
		append (string);
		return *this;
	}

	StringBase&
	operator += (const StringRef2& string)
	{
		append (string);
		return *this;
	}

	StringBase&
	operator += (const StringRef3& string)
	{
		append (string);
		return *this;
	}

	StringBase&
	operator += (const C* p)
	{
		append (p, -1);
		return *this;
	}

	StringBase&
	operator += (const C2* p)
	{
		append (p, -1);
		return *this;
	}

	StringBase&
	operator += (const C3* p)
	{
		append (p, -1);
		return *this;
	}

	StringBase&
	operator += (utf32_t x)
	{
		append (x);
		return *this;
	}

	const C&
	operator [] (intptr_t i) const
	{
		ASSERT ((size_t) i < m_length);
		return m_p [(size_t) i];
	}

	C&
	operator [] (intptr_t i)
	{
		ASSERT ((size_t) i < m_length);
		return m_p [(size_t) i];
	}

	C*
	p ()
	{
		return m_p;
	}

	const C*
	sz () const
	{
		ASSERT (!this->m_length || this->m_isNullTerminated);
		return this->m_length ? this->m_p : Details::getEmptyString ();
	}

	const C*
	szn () const
	{
		ASSERT (!this->m_length || this->m_isNullTerminated);
		return this->m_length ? this->m_p : NULL;
	}

	void
	clear ()
	{
		if (!this->m_hdr)
		{
			ASSERT (!this->m_length);
			return;
		}

		if (this->m_hdr->getRefCount () != 1)
		{
			this->release ();
			return;
		}

		this->m_p = (C*) (this->m_hdr + 1);
		this->m_p [0] = 0;
		this->m_length = 0;
	}

	size_t
	forceCopy (const StringRef& src)
	{
		return copy (src.cp (), src.getLength ());
	}

	size_t
	copy (const StringRef& src)
	{
		if (&src == this)
			return this->m_length;

		if (src.isEmpty ())
		{
			clear ();
			return 0;
		}

		ref::BufHdr* hdr = src.getHdr ();
		if (!hdr || (hdr->getFlags () & ref::BufHdrFlag_Exclusive) || !src.isNullTerminated ())
			return copy (src.cp (), src.getLength ());

		this->attach (src);
		return this->m_length;
	}

	size_t
	copy (const StringRef2& src)
	{
		return copy (src.cp (), src.getLength ());
	}

	size_t
	copy (const StringRef3& src)
	{
		return copy (src.cp (), src.getLength ());
	}

	size_t
	copy (
		const C* p,
		size_t length = -1
		)
	{
		if (p == this->m_p && (length == -1 || length == this->m_length))
			return this->m_length;

		if (length == -1)
			length = Details::calcLength (p);

		if (!length)
		{
			clear ();
			return 0;
		}

		if (!createBuffer (length, false))
			return -1;

		Details::copy (this->m_p, p, length);
		return length;
	}

	size_t
	copy (
		const C2* p,
		size_t length = -1
		)
	{
		if (length == -1)
			length = Details2::calcLength (p);

		if (!length)
		{
			clear ();
			return 0;
		}

		size_t newLength = enc::UtfConvert <Encoding, Encoding2>::calcRequiredLength (p, length);
		if (!createBuffer (newLength, false))
			return -1;

		enc::UtfConvert <Encoding, Encoding2>::convert (this->m_p, newLength, p, length);
		return newLength;
	}

	size_t
	copy (
		const C3* p,
		size_t length = -1
		)
	{
		if (length == -1)
			length = Details3::calcLength (p);

		if (!length)
		{
			clear ();
			return 0;
		}

		size_t newLength = enc::UtfConvert <Encoding, Encoding3>::calcRequiredLength (p, length);
		if (!createBuffer (newLength, false))
			return -1;

		enc::UtfConvert <Encoding, Encoding3>::convert (this->m_p, newLength, p, length);
		return newLength;
	}

	size_t
	copy (utf32_t x)
	{
		if (!x)
		{
			clear ();
			return 0;
		}

		return copy (x, 1);		
	}

	size_t
	copy (
		utf32_t x,
		size_t count
		)
	{
		if (!count)
		{
			clear ();
			return 0;
		}

		size_t codePointLength = Encoding::getEncodeCodePointLength (x);
		if (codePointLength == -1)
			return -1;

		ASSERT (codePointLength <= 4);
		
		size_t newLength = count * codePointLength;
		if (!createBuffer (newLength, false))
			return -1;

		C pattern [sizeof (utf32_t) / sizeof (C)];
		Encoding::encodeCodePoint (pattern, x);
		fillWithPattern (this->m_p, pattern, codePointLength, count);
		return newLength;
	}

	size_t
	append (const StringRef& src)
	{
		return insert (-1, src);
	}

	size_t
	append (const StringRef2& src)
	{
		return insert (-1, src);
	}

	size_t
	append (const StringRef3& src)
	{
		return insert (-1, src);
	}

	size_t
	append (
		const C* p,
		size_t length = -1
		)
	{
		return insert (-1, p, length);
	}

	size_t
	append (
		const C2* p,
		size_t length = -1
		)
	{
		return insert (-1, p, length);
	}

	size_t
	append (
		const C3* p,
		size_t length = -1
		)
	{
		return insert (-1, p, length);
	}

	size_t
	append (utf32_t x)
	{
		return x ? append (x, 1) : this->m_length;
	}

	size_t
	append (
		utf32_t x,
		size_t count
		)
	{
		return insert (-1, x, count);
	}

	size_t
	appendNewLine ()
	{
		return insertNewLine (-1);
	}

	size_t
	insert (
		size_t index,
		const StringRef& src
		)
	{
		return !this->m_length ? copy (src) : insert (index, src.cp (), src.getLength ());
	}

	size_t
	insert (
		size_t index,
		const StringRef2& src
		)
	{
		return insert (index, src.cp (), src.getLength ());
	}

	size_t
	insert (
		size_t index,
		const StringRef3& src		
		)
	{
		return insert (index, src.cp (), src.getLength ());
	}

	size_t
	insert (
		size_t index,
		const C* p,
		size_t length = -1
		)
	{
		size_t oldLength = this->m_length;

		if (length == -1)
			length = Details::calcLength (p);

		if (length == 0)
			return oldLength;

		C* dst = insertSpace (index, length);
		if (!dst)
			return -1;

		Details::copy (dst, p, length);
		return oldLength + length;
	}

	size_t
	insert (
		size_t index,
		const C2* p,
		size_t length = -1
		)
	{
		size_t oldLength = this->m_length;

		if (length == -1)
			length = Details2::calcLength (p);

		if (length == 0)
			return oldLength;

		size_t insertLength = enc::UtfConvert <Encoding, Encoding2>::calcRequiredLength (p, length);
		C* dst = insertSpace (index, insertLength);
		if (!dst)
			return -1;

		enc::UtfConvert <Encoding, Encoding2>::convert (dst, insertLength, p, length);
		return oldLength + insertLength;
	}

	size_t
	insert (
		size_t index,
		const C3* p,
		size_t length = -1
		)
	{
		size_t oldLength = this->m_length;

		if (length == -1)
			length = Details3::calcLength (p);

		if (length == 0)
			return oldLength;

		size_t insertLength = enc::UtfConvert <Encoding, Encoding3>::calcRequiredLength (p, length);
		C* dst = insertSpace (index, insertLength);
		if (!dst)
			return -1;

		enc::UtfConvert <Encoding, Encoding3>::convert (dst, insertLength, p, length);
		return oldLength + insertLength;
	}

	size_t
	insert (
		size_t index,
		utf32_t x
		)
	{
		return x ? insert (index, x, 1) : this->m_length;
	}

	size_t
	insert (
		size_t index,
		utf32_t x,
		size_t count
		)
	{
		size_t oldLength = this->m_length;

		if (count == 0)
			return oldLength;

		size_t codePointLength = Encoding::getEncodeCodePointLength (x);
		if (codePointLength == -1)
			return -1;

		ASSERT (codePointLength <= 4);

		size_t insertLength = count * codePointLength;

		C* dst = insertSpace (index, count * codePointLength);
		if (!dst)
			return -1;

		C pattern [sizeof (utf32_t) / sizeof (C)];
		Encoding::encodeCodePoint (pattern, x);
		fillWithPattern (dst, pattern, codePointLength, count);
		return oldLength + insertLength;
	}

	size_t
	insertNewLine (size_t index)
	{
#if (_AXL_OS_WIN)
		return insert (index, Details::getCrLf (), 2);
#else
		return insert (index, '\n');
#endif
	}

	size_t 
	trimLeft ()
	{
		static StringRef whitespace (Details::getWhitespace (), 4);
		size_t i = this->findNotOneOf (whitespace);
		if (i != -1)
		{
			this->m_p += i;
			this->m_length -= i;
		}

		return this->m_length;
	}

	size_t 
	trimRight ()
	{
		static StringRef whitespace (Details::getWhitespace (), 4);
		size_t i = this->reverseFindNotOneOf (whitespace);
		if (i != -1)
			setReducedLength (i + 1);

		return this->m_length;
	}

	size_t 
	trim ()
	{
		trimLeft ();
		return trimRight ();
	}

	size_t 
	replace (
		C from,
		C to
		)
	{
		bool result = ensureExclusive ();
		if (!result)
			return -1;

		size_t count = 0;
		C* p = this->m_p;
		C* end = p + this->m_length;

		for (; p < end; p++)
			if (*p == from)
				*p = to;

		return count;
	}

	template <typename CaseOp>
	size_t
	convertCase ()
	{
		StringRef src = *this; // save old contents -- can't convert in-place because length can increase

		size_t length = enc::UtfConvert <Encoding, Encoding, CaseOp>::calcRequiredLength (this->m_p, this->m_length);
		C* p = createBuffer (length);
		if (!p)
			return -1;

		enc::UtfConvert <Encoding, Encoding, CaseOp>::convert (p, length, src.cp (), src.getLength ());
		return length;
	}

	size_t 
	makeLowerCase ()
	{
		return convertCase <enc::UtfToLowerCase> ();
	}

	size_t 
	makeUpperCase ()
	{
		return convertCase <enc::UtfToUpperCase> ();
	}

	size_t 
	makeCaseFolded ()
	{
		return convertCase <enc::UtfToCaseFolded> ();
	}

	size_t
	format_va (
		const C* formatString,
		axl_va_list va
		)
	{
		size_t length = Details::calcFormatLength_va (formatString, va);
		if (!createBuffer (length, false))
			return -1;

		Details::format_va (this->m_p, length + 1, formatString, va);
		return length;
	}

	size_t
	format (
		const C* formatString,
		...
		)
	{
		AXL_VA_DECL (va, formatString);
		return format_va (formatString, va);
	}

	size_t
	appendFormat_va (
		const C* formatString,
		axl_va_list va
		)
	{
		size_t appendLength = Details::calcFormatLength_va (formatString, va);
		size_t oldLength = this->m_length;
		size_t newLength = oldLength + appendLength;
		if (!createBuffer (newLength, true))
			return -1;

		Details::format_va (this->m_p + oldLength, appendLength + 1, formatString, va);
		return newLength;
	}

	size_t
	appendFormat (
		const C* formatString,
		...
		)
	{
		AXL_VA_DECL (va, formatString);
		return appendFormat_va (formatString, va);
	}

	static
	StringBase
	format_sva (
		const C* formatString,
		axl_va_list va
		)
	{
		StringBase result;
		result.format_va (formatString, va);
		return result;
	}

	static
	StringBase
	format_s (
		const C* formatString,
		...
		)
	{
		AXL_VA_DECL (va, formatString);
		return format_sva (formatString, va);
	}

	size_t
	reduceLength (size_t delta)
	{
		if (this->m_length <= delta)
			clear ();
		else
			setReducedLength (this->m_length - delta);

		return this->m_length;
	}

	bool
	setReducedLength (size_t length)
	{
		if (length >= this->m_length)
		{
			ASSERT (length == this->m_length); // misuse otherwise
			return true;
		}

		if (!length)
		{
			clear ();
			return true;
		}

		ASSERT (this->m_p && this->m_hdr);
		
		bool isNullTerminated = !this->m_p [length];
		if (!isNullTerminated && this->m_hdr->getRefCount () == 1)
		{
			this->m_p [length] = 0;
			isNullTerminated = true;
		}

		this->m_length = length;
		return isNullTerminated || createBuffer (length, true) != NULL;
	}

	bool
	isExclusive ()
	{
		return !this->m_length || this->m_hdr && this->m_hdr->getRefCount () == 1;
	}

	bool
	ensureExclusive ()
	{
		return this->m_length ? createBuffer (this->m_length, true) != NULL : true;
	}

	C*
	getBuffer (size_t* length = NULL)
	{
		C* p = createBuffer (this->m_length, true);
		if (!p)
			return NULL;

		if (length)
		{
			size_t fullLength = this->m_hdr->getLeftoverBufferSize (this->m_p) / sizeof (C);
			ASSERT (fullLength);

			*length = fullLength - 1;
		}

		return p;
	}

	C*
	createBuffer (
		size_t length,
		bool saveContents = false
		)
	{			
		size_t size = (length + 1) * sizeof (C);

		if (this->m_hdr &&
			this->m_hdr->m_bufferSize >= size &&
			this->m_hdr->getRefCount () == 1)
		{
			if (!this->m_length || !saveContents)
				this->m_p = (C*) (this->m_hdr + 1);

			if (this->m_hdr->getLeftoverBufferSize (this->m_p) >= size)
			{
				this->m_length = length;
				this->m_p [length] = 0;
				this->m_isNullTerminated = true;
				return this->m_p;
			}
		}

		size_t bufferSize = getMinPower2Ge (size);

		ref::Ptr <ref::BufHdr> hdr = AXL_REF_NEW_EXTRA (ref::BufHdr, bufferSize);
		if (!hdr)
			return NULL;

		hdr->m_bufferSize = bufferSize;

		C* p = (C*) (hdr + 1);

		if (saveContents && this->m_p)
		{
			size_t copyLength = AXL_MIN (length, this->m_length);
			Details::copy (p, this->m_p, copyLength);
		}

		if (this->m_hdr)
			this->m_hdr->release ();

		this->m_p = p;
		this->m_hdr = hdr.detach ();
		this->m_length = length;
		this->m_isNullTerminated = true; // AXL_REF_NEW zeroes memory
		return p;
	}

	size_t
	setBuffer (
		ref::BufKind kind,
		void* p,
		size_t size
		)
	{
		ASSERT (size >= sizeof (ref::BufHdr) + sizeof (C));

		uint_t flags = kind != ref::BufKind_Static ? ref::BufHdrFlag_Exclusive : 0;
		size_t bufferSize = size - sizeof (ref::BufHdr);
		
		ref::Ptr <ref::BufHdr> hdr = AXL_REF_NEW_INPLACE (ref::BufHdr, p, flags);
		hdr->m_bufferSize = bufferSize;

		if (this->m_hdr)
			this->m_hdr->release ();

		this->m_p = (C*) (hdr + 1);
		this->m_p [0] = 0;
		this->m_hdr = hdr.detach ();
		this->m_length = 0;
		this->m_isNullTerminated = true;
		return bufferSize / sizeof (C) - 1;
	}

	C*
	reserve (
		size_t length,
		bool saveContents = false
		)
	{
		if (saveContents && length < this->m_length)
			length = this->m_length;

		size_t oldLength = this->m_length;

		if (!createBuffer (length, saveContents))
			return NULL;

		this->m_p [oldLength] = 0;
		this->m_length = oldLength;
		this->m_isNullTerminated = true;
		return this->m_p;
	}

	size_t
	updateLength ()
	{
		if (!this->m_hdr)
			return 0;

		size_t fullLength = this->m_hdr->getLeftoverBufferSize (this->m_p) / sizeof (C);
		ASSERT (fullLength);
		
		this->m_length = Details::calcLength (this->m_p, fullLength - 1);
		return this->m_length;
	}

protected:
	C*
	insertSpace (
		size_t index,
		size_t length
		)
	{
		size_t oldLength = this->m_length;

		if (!createBuffer (oldLength + length, true))
			return NULL;

		if (index > oldLength)
			index = oldLength;

		C* dst = this->m_p + index;

		if (length && index < oldLength)
			Details::move (dst + length, dst, oldLength - index);

		return dst;
	}

	static
	void
	fillWithPattern (
		C* p,
		const C* pattern,
		size_t patternLength,
		size_t count
		)
	{
		if (patternLength == 1)
		{
			Details::fill (p, *pattern, count);
			return;
		}

		C* end = p + count * patternLength;

		for (; p < end; p += patternLength)
			Details::copy (p, pattern, patternLength);
	}
};

//.............................................................................

typedef StringRefBase <char>    StringRef;
typedef StringRefBase <wchar_t> StringRef_w;
typedef StringRefBase <utf8_t>  StringRef_utf8;
typedef StringRefBase <utf16_t> StringRef_utf16;
typedef StringRefBase <utf32_t> StringRef_utf32;

typedef StringBase <char>    String;
typedef StringBase <wchar_t> String_w;
typedef StringBase <utf8_t>  String_utf8;
typedef StringBase <utf16_t> String_utf16;
typedef StringBase <utf32_t> String_utf32;

//. . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .

// specializations for ArgType

template <>
class ArgType <String_utf8>
{
public:
	typedef const StringRef_utf8& Type;
};

template <>
class ArgType <String_utf16>
{
public:
	typedef const StringRef_utf16& Type;
};

template <>
class ArgType <String_utf32>
{
public:
	typedef const StringRef_utf32& Type;
};


//.............................................................................

inline
String
formatString_va (
	const char* formatString,
	axl_va_list va
	)
{
	return String::format_sva (formatString, va);
}

inline
String
formatString (
	const char* formatString,
	...
	)
{
	AXL_VA_DECL (va, formatString);
	return String::format_sva (formatString, va);
}

//.............................................................................

} // namespace sl
} // namespace axl
