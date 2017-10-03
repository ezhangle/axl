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

#define _AXL_IO_SERIALSETTINGS_H

#include "axl_g_Pch.h"

namespace axl {
namespace io {

//..............................................................................

enum SerialFlowControl
{
	SerialFlowControl_None = 0,
	SerialFlowControl_RtsCts,
	SerialFlowControl_XonXoff,
};

// . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .

enum SerialStopBits
{
	SerialStopBits_1  = 0,
	SerialStopBits_15 = 1,
	SerialStopBits_2  = 2,
};


// . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .

enum SerialParity
{
	SerialParity_None  = 0,
	SerialParity_Odd   = 1,
	SerialParity_Even  = 2,
	SerialParity_Mark  = 3,
	SerialParity_Space = 4,
};

// . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .

enum SerialStatusLine
{
	SerialStatusLine_Cts  = 0x01,
	SerialStatusLine_Dsr  = 0x02,
	SerialStatusLine_Ring = 0x04,
	SerialStatusLine_Dcd  = 0x08,
};

// . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .

enum SerialSettingId
{
	SerialSettingId_BaudRate     = 0x01,
	SerialSettingId_FlowControl  = 0x02,
	SerialSettingId_DataBits     = 0x04,
	SerialSettingId_StopBits     = 0x08,
	SerialSettingId_Parity       = 0x10,
	SerialSettingId_ReadInterval = 0x20,
};

// . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .

struct SerialSettings
{
	uint_t m_baudRate;
	SerialFlowControl m_flowControl;
	uint_t m_dataBits;
	SerialStopBits m_stopBits;
	SerialParity m_parity;
	uint_t m_readInterval; // inverse of COMMTIMEOUTS.ReadIntervalTimeout (which always makes me confused):
	                       // 0  -- return immediatly
	                       // -1 -- wait for the buffer to fill completely

	SerialSettings ()
	{
		setup (38400);
	}

	SerialSettings (
		uint_t baudRate,
		SerialFlowControl flowControl = SerialFlowControl_None,
		uint_t dataBits = 8,
		SerialStopBits stopBits = SerialStopBits_1,
		SerialParity parity = SerialParity_None,
		uint_t readInterval = 10 // 10ms can be used in general case
		)
	{
		setup (baudRate, flowControl, dataBits, stopBits, parity, readInterval);
	}

	void
	setup (
		uint_t baudRate,
		SerialFlowControl flowControl = SerialFlowControl_None,
		uint_t dataBits = 8,
		SerialStopBits stopBits = SerialStopBits_1,
		SerialParity parity = SerialParity_None,
		uint_t readInterval = 10
		)
	{
		m_baudRate = baudRate;
		m_flowControl = flowControl;
		m_dataBits = dataBits;
		m_stopBits = stopBits;
		m_parity = parity;
		m_readInterval = readInterval;
	}

#if (_AXL_OS_WIN)
	void
	setDcb (const DCB* dcb);
#elif (_AXL_OS_POSIX)
	void
	setAttr (const termios* attr);
#endif
};

//..............................................................................

} // namespace io
} // namespace axl