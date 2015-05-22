#pragma once

//.............................................................................

#include "axl_g_Pch.h"

#if (_AXL_ENV == AXL_ENV_WIN)
#	include <ws2tcpip.h>
#	include <iphlpapi.h>
#	pragma comment (lib, "ws2_32.lib")
#	pragma comment (lib, "iphlpapi.lib")
#elif (_AXL_ENV == AXL_ENV_POSIX)
#	include <netdb.h>
#endif

// axl

#include "axl_rtl_String.h"
#include "axl_err_Error.h"
#include "axl_fsm_RegExp.h"
#include "axl_fsm_StdRegExpNameMgr.h"
#include "axl_rtl_AutoPtrArray.h"
#include "axl_mt_LongJmpTry.h"
#include "axl_mt_DynamicLibrary.h"
#include "axl_io_Socket.h"
#include "axl_io_File.h"
#include "axl_io_NetworkAdapter.h"
#include "axl_g_Time.h"

using namespace axl;

//.............................................................................
