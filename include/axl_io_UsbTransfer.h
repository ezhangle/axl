// This file is part of AXL (R) Library
// Tibbo Technology Inc (C) 2004-2015. All rights reserved
// Author: Vladimir Gladkov

#pragma once

#define _AXL_IO_USBTRANSFER_H

#include "axl_io_UsbError.h"
#include "axl_sl_Handle.h"

namespace axl {
namespace io {

//.............................................................................

class FreeUsbTransfer
{
public:
	void
	operator () (libusb_transfer* h)
	{
		libusb_free_transfer (h);
	}
};

//. . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .

class UsbTransfer: public sl::Handle <libusb_transfer*, FreeUsbTransfer>
{
};

//.............................................................................

} // namespace io
} // namespace axl
