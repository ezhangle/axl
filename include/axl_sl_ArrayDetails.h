// This file is part of AXL (R) Library
// Tibbo Technology Inc (C) 2004-2015. All rights reserved
// Author: Vladimir Gladkov

#pragma once

#define _AXL_SL_ARRAYDETAILS_H

#include "axl_ref_Buf.h"
#include "axl_sl_ArgType.h"

namespace axl {
namespace sl {

//..............................................................................

template <typename T>
class ReverseArray
{
public:
	typedef typename ArgType <T>::Type ValueArg;

public:
	static
	void
	reverse (
		T* dst,
		size_t count
		)
	{
		T* back = dst + count - 1;
		T* end = dst + count / 2;
		T tmp;

		for (; dst < end; dst++, back--)
		{
			tmp = *dst;
			*dst = *back;
			*back = tmp;
		}
	}

	static
	void
	copyReverse (
		T* dst,
		const T* src,
		size_t count
		)
	{
		if (src == dst) // in-place
		{
			reverse (dst, count);
		}
		else if (src + count <= dst || dst + count <= src)
		{
			copyReverseImpl (dst, src, count);
		}
		else if (src < dst)// random overlap
		{
			size_t nonOverlapCount = dst - src;
			size_t overlapCount = count - nonOverlapCount;

			reverse (dst, overlapCount);
			copyReverseImpl (dst + overlapCount, src, nonOverlapCount);
		}
		else
		{
			size_t nonOverlapCount = src - dst;
			size_t overlapCount = count - nonOverlapCount;

			reverse (dst + nonOverlapCount, overlapCount);
			copyReverseImpl (dst, src + overlapCount, nonOverlapCount);
		}
	}

protected:
	static
	void
	copyReverseImpl (
		T* dst,
		const T* src,
		size_t count
		)
	{
		const T* back = src + count - 1;
		T* end = dst + count;
		for (; dst < end; dst++, back--)
			*dst = *back;
	}
};

// . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .

// general case: full cycle of construction, copy, destruction

template <typename T>
class ArrayDetails: public ReverseArray <T>
{
public:
	class Hdr: public ref::BufHdr
	{
	public:
		size_t m_count;

		~Hdr ()
		{
			destruct ((T*) (this + 1), m_count);
		}
	};

	enum
	{
		IsSimple = false,
	};

public:
	static
	void
	setHdrCount (
		Hdr* hdr,
		size_t count
		)
	{
		hdr->m_count = count;
	}

	static
	void
	construct (
		T* p,
		size_t count
		)
	{
		memset (p, 0, count * sizeof (T)); // zero memory before construction

		T* end = p + count;
		for (; p < end; p++)
			new (p) T;
	}

	static
	void
	constructCopy (
		T* dst,
		const T* src,
		size_t count
		)
	{
		memset (dst, 0, count * sizeof (T)); // zero memory before construction

		T* end = dst + count;
		for (; dst < end; dst++, src++)
			new (dst) T (*src);
	}

	static
	void
	destruct (
		T* p,
		size_t count
		)
	{
		T* end = p + count;
		for (; p < end; p++)
			p->~T ();
	}

	static
	void
	copy (
		T* dst,
		const T* src,
		size_t count
		)
	{
		if (src > dst || src + count <= dst)
		{
			T* end = dst + count;
			for (; dst < end; dst++, src++)
				*dst = *src;
		}
		else
		{
			T* end = dst;

			dst += count;
			src += count;

			while (dst > end)
			{
				dst--;
				src--;
				*dst = *src;
			}
		}
	}

	static
	void
	clear (
		T* p,
		size_t count
		)
	{
		T* begin = p;
		T* end = p + count;

		for (; p < end; p++)
			p->~T ();

		p = begin;
		memset (p, 0, count * sizeof (T));

		for (; p < end; p++)
			new (p) T;
	}
};

// . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .

// fast memory block operations for types that do not need ctor/dtor

template <typename T>
class SimpleArrayDetails: public ReverseArray <T>
{
public:
	typedef ref::BufHdr Hdr;

	enum
	{
		IsSimple = true,
	};

public:
	static
	void
	setHdrCount (
		Hdr* hdr,
		size_t count
		)
	{
	}

	static
	void
	construct (
		T* p,
		size_t count
		)
	{
		memset (p, 0, count * sizeof (T));
	}

	static
	void
	constructCopy (
		T* dst,
		const T* src,
		size_t count
		)
	{
		memcpy (dst, src, count * sizeof (T));
	}

	static
	void
	destruct (
		T* p,
		size_t count
		)
	{
	}

	static
	void
	copy (
		T* dst,
		const T* src,
		size_t count
		)
	{
		memmove (dst, src, count * sizeof (T));
	}

	static
	void
	clear (
		T* p,
		size_t count
		)
	{
		memset (p, 0, count * sizeof (T));
	}
};

//..............................................................................

// specialization for primitive types

template <>
class ArrayDetails <char>: public SimpleArrayDetails <char>
{
};

template <>
class ArrayDetails <wchar_t>: public SimpleArrayDetails <wchar_t>
{
};

template <>
class ArrayDetails <float>: public SimpleArrayDetails <float>
{
};

template <>
class ArrayDetails <double>: public SimpleArrayDetails <double>
{
};

template <>
class ArrayDetails <int8_t>: public SimpleArrayDetails <int8_t>
{
};

template <>
class ArrayDetails <uint8_t>: public SimpleArrayDetails <uint8_t>
{
};

template <>
class ArrayDetails <int16_t>: public SimpleArrayDetails <int16_t>
{
};

template <>
class ArrayDetails <uint16_t>: public SimpleArrayDetails <uint16_t>
{
};

template <>
class ArrayDetails <int32_t>: public SimpleArrayDetails <int32_t>
{
};

template <>
class ArrayDetails <uint32_t>: public SimpleArrayDetails <uint32_t>
{
};

template <>
class ArrayDetails <int64_t>: public SimpleArrayDetails <int64_t>
{
};

template <>
class ArrayDetails <uint64_t>: public SimpleArrayDetails <uint64_t>
{
};

// . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .

// specialization for pointers

template <typename T>
class ArrayDetails <T*>: public SimpleArrayDetails <T*>
{
};

//..............................................................................

} // namespace sl
} // namespace axl
