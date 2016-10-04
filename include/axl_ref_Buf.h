// This file is part of AXL (R) Library
// Tibbo Technology Inc (C) 2004-2015. All rights reserved
// Author: Vladimir Gladkov

#pragma once

#define _AXL_REF_BUF_H

#include "axl_ref_New.h"
#include "axl_sl_Operator.h"
#include "axl_sl_BitIdx.h"

namespace axl {
namespace ref {

//.............................................................................

// ref-counted buffer for variable-sized objects 
// could be also used for fixed-sized object as single-writer multiple reader accessor
// can use external buffer (e.g. static or allocated on stack)

enum BufKind
{
	BufKind_Exclusive, // buffer cannot be shared (stack-allocated or object-field) 
	BufKind_Shared,    // buffer can be shared (static or global)

	// aliases

	BufKind_Static = BufKind_Shared, 
	BufKind_Stack  = BufKind_Exclusive,
	BufKind_Field  = BufKind_Exclusive,
};

//. . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .

enum BufHdrFlag
{
	BufHdrFlag_Exclusive = 0x04
};

//. . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .

struct BufHdr: public RefCount
{
	size_t m_bufferSize;

	const void*
	cp () const
	{
		return this + 1;
	}

	const void*
	getEnd () const
	{
		return (char*) (this + 1) + m_bufferSize;
	}

	bool
	isInsideBuffer (const void* p) const
	{
		return p >= cp () && p < getEnd ();
	}

	size_t
	getLeftoverBufferSize (const void* p) const
	{
		ASSERT (isInsideBuffer (p));
		return (char*) getEnd () - (char*) p;
	}
};

//. . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .

template <
	typename T,
	typename SizeOf = sl::SizeOf <T>
	>
class BufRef
{
protected:
	T* m_p;
	BufHdr* m_hdr;
	size_t m_size;

public:
	BufRef ()
	{
		initialize ();
	}

	BufRef (const BufRef& src)
	{
		initialize ();
		attach (src);
	}

	BufRef (const T* p)
	{
		initialize ();
		attach (NULL, p, SizeOf () (p));
	}

	BufRef (
		const T* p,
		size_t size
		)
	{
		initialize ();
		attach (NULL, p, size);
	}

	BufRef (
		const T* p,
		const void* end
		)
	{
		initialize ();
		attach (NULL, p, (char*) end - (char*) p);
	}

	BufRef (
		BufHdr* hdr,
		const T* p
		)
	{
		initialize ();
		attach (hdr, p, SizeOf () (p));
	}

	BufRef (
		BufHdr* hdr,
		const T* p,
		size_t size
		)
	{
		initialize ();
		attach (hdr, p, size);
	}

	BufRef (
		BufHdr* hdr,
		const T* p,
		const void* end
		)
	{
		initialize ();
		attach (hdr, p, (char*) end - (char*) p);
	}

	~BufRef ()
	{
		release ();
	}

	operator const T* () const
	{
		return m_p;
	}

	const T* 
	operator -> () const
	{ 
		ASSERT (m_p);
		return m_p; 
	}

	BufRef&
	operator = (const BufRef& src)
	{
		attach (src);
		return *this;
	}

	const T* 
	cp () const
	{
		return m_p;
	}

	size_t
	getSize () const
	{
		return m_size;
	}

	BufHdr* 
	getHdr () const
	{
		return m_hdr;
	}

	const T* 
	getEnd () const
	{
		return (T*) ((char*) m_p + m_size);
	}

	bool
	isEmpty () const
	{
		return m_size == 0;
	}

	void
	release ()
	{
		if (m_hdr)
			m_hdr->release ();

		initialize ();
	}

protected:
	void
	initialize ()
	{
		m_p = NULL;
		m_hdr = NULL;
		m_size = 0;
	}

	void
	attachBufHdr (BufHdr* hdr)
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
	attach (const BufRef& src)
	{
		if (&src != this)
			attach (src.m_hdr, src.m_p, src.m_size);
	}

	void
	attach (
		BufHdr* hdr,
		const T* p,
		size_t size
		)
	{
		attachBufHdr (hdr);

		m_p = (T*) p;
		m_size = size;
	}
};

//. . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .

template <
	typename T,
	typename SizeOf = sl::SizeOf <T>,
	typename Ref = BufRef <T, SizeOf>
	>
class Buf: public Ref
{
protected:
	class Hdr: public BufHdr
	{
	public:
		~Hdr ()
		{
			((T*) (this + 1))->~T ();
		}
	};

	enum
	{
		MinBufSize = sizeof (Hdr) + sizeof (T)
	};

public:
	Buf ()
	{
	}

	Buf (const Buf& src)
	{
		copy (src);
	}

	Buf (const Ref& src)
	{
		copy (src);
	}

	Buf (
		const T* src,
		size_t size = -1
		)
	{
		copy (src, size);
	}
	
	Buf (
		BufKind kind,
		void* p, 
		size_t size
		)
	{
		setBuffer (kind, p, size);
	}

	operator const T* () const
	{ 
		return m_p; 
	}

	operator T* ()
	{ 
		return m_p; 
	}

	const T* 
	operator -> () const
	{ 
		ASSERT (m_p);
		return m_p; 
	}

	T* 
	operator -> ()
	{ 
		ASSERT (m_p);
		return m_p; 
	}

	Buf& 
	operator = (const Buf& src)
	{ 
		copy (src);
		return *this;
	}

	Buf& 
	operator = (const Ref& src)
	{ 
		copy (src);
		return *this;
	}

	Buf& 
	operator = (const T* p)
	{
		copy (p, -1);
		return *this;
	}
	
	T*
	p ()
	{
		return ensureExclusive () ? m_p : NULL;
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

		if (m_size)
			this->m_p->~T ();

		this->m_p = (T*) (this->m_hdr + 1);
		this->m_size = 0;
	}

	size_t
	copy (const Ref& src)
	{
		if (&src == this)
			return this->m_size;

		BufHdr* hdr = src.getHdr ();
		if (!hdr || (hdr->getFlags () & BufHdrFlag_Exclusive))
			return copy (src, src.getSize ());

		this->attach (src);
		return this->m_size;
	}

	size_t
	copy (
		const T* p,
		size_t size = -1
		)
	{
		if (p == this->m_p && (size == -1 || size == this->m_size))
			return this->m_size;

		if (size == -1)
			size = SizeOf () (p);

		if (size < sizeof (T))
			size = sizeof (T);

		if (!createBuffer (size, false))
			return -1;

		*m_p = *p;
		if (size > sizeof (T))
			memcpy (this->m_p + 1, p + 1, size - sizeof (T));

		return size;
	}

	bool
	isExclusive ()
	{
		return !this->m_size || this->m_hdr && this->m_hdr->getRefCount () == 1;
	}

	bool 
	ensureExclusive ()
	{ 
		return m_size ? createBuffer (m_size, true) != NULL : true; 
	}

	T* 
	getBuffer (size_t* size = NULL)
	{
		T* p = createBuffer (m_size, true);
		if (!p)
			return NULL;

		if (size)
			*size = this->m_hdr->getLeftoverBufferSize (this->m_p);

		return p;
	}

	T* 
	createBuffer (
		size_t size = sizeof (T), 
		bool saveContents = false
		)
	{	
		if (size < sizeof (T))
			size = sizeof (T);

		if (this->m_hdr &&
			this->m_hdr->m_bufferSize >= size &&
			this->m_hdr->getRefCount () == 1)
		{
			if (!this->m_size)
			{
				ASSERT (this->m_p == (T*) (this->m_hdr + 1));
				new (this->m_p) T;
			}
			else if (!saveContents)
			{
				// no need to call destructor on old m_p -- in-buffer shifts are only applicable to non-destructible types
				this->m_p = (T*) (this->m_hdr + 1);
			}

			if (this->m_hdr->getLeftoverBufferSize (this->m_p) >= size)
			{
				this->m_size = size;
				return this->m_p;
			}
		}

		size_t bufferSize = sl::getMinPower2Ge (size);

		Ptr <Hdr> hdr = AXL_REF_NEW_EXTRA (Hdr, bufferSize);
		if (!hdr)
			return NULL;

		hdr->m_bufferSize = bufferSize;

		T* p = (T*) (hdr + 1);

		if (saveContents && this->m_p)
		{
			new (p) T (*m_p);
			size_t copySize = AXL_MIN (size, this->m_size);
			if (copySize > sizeof (T))
				memcpy (p + 1, m_p + 1, copySize - sizeof (T));
		}
		else
		{
			new (p) T;
		}

		if (this->m_hdr)
			this->m_hdr->release ();

		this->m_p = p;
		this->m_hdr = hdr.detach ();
		this->m_size = size;
		return p;
	}

	size_t
	setBuffer (
		ref::BufKind kind,
		void* p,
		size_t size
		)
	{
		ASSERT (size >= MinBufSize);

		uint_t flags = kind != ref::BufKind_Static ? ref::BufHdrFlag_Exclusive : 0;
		size_t bufferSize = size - sizeof (ref::BufHdr);
		
		Ptr <Hdr> hdr = AXL_REF_NEW_INPLACE (Hdr, p, flags);
		hdr->m_bufferSize = bufferSize;

		if (this->m_hdr)
			this->m_hdr->release ();

		this->m_p = (T*) (hdr + 1);
		this->m_hdr = hdr.detach ();
		this->m_size = 0;

		return bufferSize;
	}
};

//.............................................................................

} // namespace ref
} // namespace axl

