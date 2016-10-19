// This file is part of AXL (R) Library
// Tibbo Technology Inc (C) 2004-2015. All rights reserved
// Author: Vladimir Gladkov

#pragma once

#define _AXL_MEM_ALLOCATOR_H

#include "axl_mem_Tracker.h"

#if (defined _AXL_MEM_ALLOCATE_IMPL && defined _AXL_MEM_FREE_IMPL)

extern "C"
void*
_AXL_MEM_ALLOCATE_IMPL (size_t size);

extern "C"
void
_AXL_MEM_FREE_IMPL (void* size);

#endif

namespace axl {
namespace mem {

//..............................................................................

class DirectAllocator
{
public:
#if (defined _AXL_MEM_ALLOCATE_IMPL && defined _AXL_MEM_FREE_IMPL)
	static
	void*
	allocate (size_t size)
	{
		return ::_AXL_MEM_ALLOCATE_IMPL (size);
	}

	static
	void
	free (void* p)
	{
		::_AXL_MEM_FREE_IMPL (p);
	}
#else
	static
	void*
	allocate (size_t size)
	{
		return ::malloc (size);
	}

	static
	void
	free (void* p)
	{
		::free (p);
	}
#endif
};

// . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .

class ZeroAllocator: public DirectAllocator
{
public:
	static
	void*
	allocate (size_t size)
	{
		void* p = DirectAllocator::allocate (size);
		if (p)
			memset (p, 0, size);
		return p;
	}
};

//..............................................................................

template <typename BaseAllocator>
class TrackingAllocator
{
public:
	static
	void*
	allocate (
		size_t size,
		const char* tag,
		const char* filePath,
		int line
		)
	{
		size_t allocSize = size + sizeof (Tracker::BlockHdr);

		Tracker::BlockHdr* hdr = (Tracker::BlockHdr*) BaseAllocator::allocate (allocSize);
		if (!hdr)
			return NULL;

		hdr->m_size = size;
		hdr->m_tag = tag;
		hdr->m_filePath = filePath;
		hdr->m_line = line;

		getTracker ()->add (hdr);

		return hdr + 1;
	}

	static
	void
	free (void* p)
	{
		Tracker::BlockHdr* hdr = (Tracker::BlockHdr*) p - 1;
		getTracker ()->remove (hdr);
		BaseAllocator::free (hdr);
	}
};

//..............................................................................

template <typename BaseAllocator>
class Allocate
{
public:
	void*
	operator () (size_t size)
	{
		return BaseAllocator::allocate (size);
	}
};

// . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .

template <typename BaseAllocator>
class Free
{
public:
	void
	operator () (void* p)
	{
		BaseAllocator::free (p);
	}
};

//..............................................................................

template <typename BaseAllocator>
class TrackingAllocate
{
public:
	void*
	operator () (
		size_t size,
		const char* tag,
		const char* filePath,
		int line
		)
	{
		return TrackingAllocator <BaseAllocator>::allocate (size, tag, filePath, line);
	}
};

// . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .

template <typename BaseAllocator>
class TrackingFree
{
public:
	void
	operator () (void* p)
	{
		TrackingAllocator <BaseAllocator>::free (p);
	}
};

//..............................................................................

#ifdef _AXL_DEBUG

typedef TrackingAllocator <DirectAllocator> StdAllocator;
typedef TrackingAllocator <ZeroAllocator>   StdZeroAllocator;
typedef TrackingAllocate <DirectAllocator>  StdAllocate;
typedef TrackingAllocate <ZeroAllocator>    StdZeroAllocate;
typedef TrackingFree <DirectAllocator>      StdFree;

#else

typedef DirectAllocator            StdAllocator;
typedef ZeroAllocator              StdZeroAllocator;
typedef Allocate <DirectAllocator> StdAllocate;
typedef Allocate <ZeroAllocator>   StdZeroAllocate;
typedef Free <DirectAllocator>     StdFree;

#endif

//..............................................................................

#ifdef _AXL_DEBUG

#define AXL_MEM_ALLOCATE_EX(size, tag) \
	(axl::mem::StdAllocator::allocate (size, tag, __FILE__, __LINE__))

#define AXL_MEM_ZERO_ALLOCATE_EX(size, tag) \
	(axl::mem::StdZeroAllocator::allocate (size, tag, __FILE__, __LINE__))

#else

#define AXL_MEM_ALLOCATE_EX(size, tag) \
	(axl::mem::StdAllocator::allocate (size))

#define AXL_MEM_ZERO_ALLOCATE_EX(size, tag) \
	(axl::mem::StdZeroAllocator::allocate (size))

#endif

#define AXL_MEM_ALLOCATE(size) \
	AXL_MEM_ALLOCATE_EX (size, "<buffer>")

#define AXL_MEM_ZERO_ALLOCATE(size) \
	AXL_MEM_ZERO_ALLOCATE_EX (size, "<buffer>")

#define AXL_MEM_FREE(p) \
	(axl::mem::StdAllocator::free (p))

//..............................................................................

} // namespace mem
} // namespace axl
