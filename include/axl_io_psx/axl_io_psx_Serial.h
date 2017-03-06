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

#define _AXL_PSX_SERIAL_H

#include "axl_io_psx_Fd.h"

namespace axl {
namespace io {
namespace psx {

//..............................................................................

class Serial: public Fd
{
public:
	bool
	open (const sl::StringRef& name)
	{
		return
			Fd::open (name, O_RDWR | O_NONBLOCK | O_NOCTTY, 0) &&
			setBlockingMode (true);
	}

	bool
	getAttr (termios* attr) const
	{
		int result = ::tcgetattr (m_h, attr);
		return err::complete (result != -1);
	}

	bool
	setAttr (
		const termios* attr,
		int action = TCSANOW
		)
	{
		int result = ::tcsetattr (m_h, action, attr);
		return err::complete (result != -1);
	}

	bool
	drain ()
	{
		int result = ::tcdrain (m_h);
		return err::complete (result != -1);
	}

	bool
	flush (int queueSelector = TCIOFLUSH)
	{
		int result = ::tcflush (m_h, queueSelector);
		return err::complete (result != -1);
	}

	bool
	flow (int action)
	{
		int result = ::tcflow (m_h, action);
		return err::complete (result != -1);
	}

	uint_t
	getStatusLines () const;

	bool
	setDtr (bool isSet);

	bool
	setRts (bool isSet);

#if (!_AXL_OS_DARWIN)
	bool
	wait (uint_t mask)
	{
		int result = ::ioctl (m_h, TIOCMIWAIT, mask);
		return err::complete (result != -1);
	}
#endif
};

//..............................................................................

} // namespace psx
} // namespace io
} // namespace axl