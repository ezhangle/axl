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

#define _AXL_SYS_READWRITELOCK_H

#include "axl_sys_Atomic.h"
#include "axl_sys_Event.h"
#include "axl_io_Mapping.h"

namespace axl {
namespace sys {

//..............................................................................

class ReadWriteLock
{
protected:
	// locking data may be shared between processes

	struct Data
	{
		volatile int32_t m_lock;
		volatile uint32_t m_activeReadCount;
		volatile uint32_t m_queuedReadCount;
		volatile uint32_t m_activeWriteCount; // one or zero
		volatile uint32_t m_queuedWriteCount;
	};

protected:
	Data* m_data;
	io::File m_file;
	io::Mapping m_mapping;
	NameableNotificationEvent m_readEvent;
	NameableEvent m_writeEvent;

public:
	ReadWriteLock ()
	{
		m_data = NULL;
	}

	~ReadWriteLock ()
	{
		close ();
	}

	void
	close ();

	bool
	create ();

	bool
	create (
		const sl::StringRef& fileName,
		const sl::StringRef& readEventName,
		const sl::StringRef& writeEventName
		);

	bool
	open (
		const sl::StringRef& fileName,
		const sl::StringRef& readEventName,
		const sl::StringRef& writeEventName
		);

	bool
	readLock (uint_t timeout = -1);

	void
	readUnlock ();

	bool
	writeLock (uint_t timeout = -1);

	void
	writeUnlock ();
};

//..............................................................................

} // namespace sys
} // namespace axl
