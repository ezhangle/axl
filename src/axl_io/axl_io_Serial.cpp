#include "pch.h"
#include "axl_io_Serial.h"

namespace axl {
namespace io {

//.............................................................................

bool 
CSerial::Open (const char* pName)
{
	Close ();

	char DeviceName [MAX_PATH + 1] = { 0 };
 
	if (strncmp (pName, "\\\\.\\", 4) != 0)
	{
		_snprintf (DeviceName, MAX_PATH, "\\\\.\\%s", pName);
		DeviceName [MAX_PATH] = 0;
		pName = DeviceName;
	}

	return false;
}

void 
CSerial::Close ()
{
}

bool 
CSerial::SetSettings (
	const TSerialSettings* pSettings,
	int Mask
	)
{
	return false;
}

bool 
CSerial::GetSettings (TSerialSettings* pSettings)
{
	return false;
}

bool
CSerial::SetControlLines (
	int Lines,
	int Mask
	)
{
	return false;
}

int
CSerial::GetControlLines ()
{
	return 0;
}

int
CSerial::GetStatusLines ()
{
	return 0;
}

bool
CSerial::SetEventHandler (
	int Mask,
	const exe::CFunction& OnEvent
	)
{
	return false;
}

//.............................................................................

} // namespace io
} // namespace axl

