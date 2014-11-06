// This file is part of AXL (R) Library
// Tibbo Technology Inc (C) 2004-2014. All rights reserved
// Author: Vladimir Gladkov

#pragma once

#define _AXL_IO_MAPPING_H

#include "axl_io_File.h"

#if (_AXL_ENV == AXL_ENV_WIN)
#	include "axl_io_win_Mapping.h"
#elif (_AXL_ENV == AXL_ENV_POSIX)
#	include "axl_io_psx_Mapping.h"
#	include "axl_rtl_String.h"
#endif

namespace axl {
namespace io {

//.............................................................................

class Mapping
{
protected:
	void* m_p;
	size_t m_size;

#if (_AXL_ENV == AXL_ENV_WIN)
	win::Mapping m_mapping;
	win::MappedView m_view;
#elif (_AXL_ENV == AXL_ENV_POSIX)
	psx::Mapping m_mapping;
	psx::SharedMemory m_sharedMemory;
	rtl::String m_sharedMemoryName;
#endif

public:
	Mapping ()
	{
		m_p = NULL;
		m_size = 0;
	}

	operator void* ()
	{
		return m_p;
	}

	bool
	isOpen ()
	{
		return m_p != NULL;
	}

	void*
	p ()
	{
		return m_p;
	}

	size_t
	getSize ()
	{
		return m_size;
	}

	void*
	open (
		File* file,
		uint64_t offset,
		size_t size,
		uint_t flags = 0 // EFileFlag
		);

	void*
	open (
		File* file,
		uint_t flags = 0 // EFileFlag
		)
	{
		return open (file, 0, -1, flags);
	}

	void*
	open (
		const char* name,
		size_t size,
		uint_t flags = 0 // EFileFlag
		);

	void
	close ();
};

//.............................................................................

} // namespace io
} // namespace axl