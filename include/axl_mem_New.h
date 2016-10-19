// This file is part of AXL (R) Library
// Tibbo Technology Inc (C) 2004-2015. All rights reserved
// Author: Vladimir Gladkov

#pragma once

#define _AXL_MEM_NEW_H

#include "axl_mem_Allocator.h"

namespace axl {
namespace mem {

//..............................................................................

template <typename T>
class StdDelete
{
public:
	void
	operator () (T* p)
	{
		p->~T ();
		StdAllocator::free (p);
	}
};

// . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .

template <typename T>
class CppDelete
{
public:
	void
	operator () (T* p)
	{
		delete p;
	}
};

//..............................................................................

template <typename T>
void
stdDelete (T* p)
{
	p->~T ();
	StdAllocator::free (p);
}

// . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .

#ifdef _AXL_DEBUG

#define AXL_MEM_NEW(T) \
	(new (AXL_MEM_ZERO_ALLOCATE_EX (sizeof (T), #T)) T)

#define AXL_MEM_NEW_EXTRA(T, extra) \
	(new (AXL_MEM_ZERO_ALLOCATE_EX (sizeof (T) + extra, #T)) T)

#define AXL_MEM_NEW_ARGS(T, args) \
	(new (AXL_MEM_ZERO_ALLOCATE_EX (sizeof (T), #T)) T args)

#define AXL_MEM_NEW_ARGS_EXTRA(T, args, extra) \
	(new (AXL_MEM_ZERO_ALLOCATE_EX (sizeof (T) + extra, #T)) T args)

#else

#define AXL_MEM_NEW(T) \
	(new (AXL_MEM_ZERO_ALLOCATE (sizeof (T))) T)

#define AXL_MEM_NEW_EXTRA(T, extra) \
	(new (AXL_MEM_ZERO_ALLOCATE (sizeof (T) + extra)) T)

#define AXL_MEM_NEW_ARGS(T, args) \
	(new (AXL_MEM_ZERO_ALLOCATE (sizeof (T))) T args)

#define AXL_MEM_NEW_ARGS_EXTRA(T, args, extra) \
	(new (AXL_MEM_ZERO_ALLOCATE (sizeof (T) + extra)) T args)

#endif

#define AXL_MEM_DELETE(p) \
	(axl::mem::stdDelete (p))

//..............................................................................

} // namespace mem
} // namespace axl
