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

#define _AXL_SL_AUTOPTRARRAY_H

#include "axl_sl_Array.h"
#include "axl_mem_New.h"

namespace axl {
namespace sl {

//..............................................................................

template <
	typename T,
	typename Delete_0 = typename mem::StdDelete <T>
	>
class AutoPtrArray: public Array <T*>
{
	AXL_DISABLE_COPY (AutoPtrArray)

public:
	typedef Array <T*> BaseType;
	typedef Delete_0 Delete;

public:
	AutoPtrArray ():
		BaseType ()
	{
	}

	AutoPtrArray (T* e):
		BaseType (e)
	{
	}

	AutoPtrArray (
		T* const* p,
		size_t count
		):
		BaseType (p, count)
	{
	}

	AutoPtrArray (
		ref::BufKind bufKind,
		void* p,
		size_t size
		):
		BaseType (bufKind, p, size)
	{
	}

	~AutoPtrArray ()
	{
		deleteElements ();
	}

	void
	clear ()
	{
		deleteElements ();
		BaseType::clear ();
	}

	void
	takeOver (AutoPtrArray* src)
	{
		deleteElements ();
		this->release ();
		this->m_p = src->m_p;
		src->m_p = NULL;
	}

protected:
	void
	deleteElements ()
	{
		size_t count = this->getCount ();

		for (size_t i = 0; i < count; i++)
		{
			T* e = this->m_p [i];
			if (e)
				Delete () (e);
		}
	}
};

//..............................................................................

} // namespace sl
} // namespace axl