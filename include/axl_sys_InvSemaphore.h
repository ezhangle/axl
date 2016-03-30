// This file is part of AXL (R) Library
// Tibbo Technology Inc (C) 2004-2015. All rights reserved
// Author: Vladimir Gladkov

#pragma once

#define _AXL_SYS_INVSEMAPHORE_H

#include "axl_sys_Lock.h"
#include "axl_sys_Event.h"

namespace axl {
namespace sys {

//.............................................................................

class InvSemaphore: public NotificationEvent
{
protected:
	Lock m_lock;
	intptr_t m_count;

public:
	InvSemaphore (intptr_t count = 0)
	{
		setImpl (count);
	}

	void
	set (intptr_t count)
	{
		m_lock.lock ();
		setImpl (count);
		m_lock.unlock ();
	}

	void
	add (intptr_t delta)
	{
		m_lock.lock ();
		setImpl (m_count + delta);
		m_lock.unlock ();
	}

protected:
	void
	setImpl (intptr_t count) // called under lock
	{
		m_count = count;
		
		if (m_count)
			reset ();
		else
			signal ();
	}

};

//.............................................................................

} // namespace sys
} // namespace axl
