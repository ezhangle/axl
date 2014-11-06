#pragma once

// The following macros define the minimum required platform.  The minimum required platform
// is the earliest version of Windows, Internet Explorer etc. that has the necessary features to run
// your application.  The macros work by enabling all features available on platform versions up to and
// including the version specified.

// Modify the following defines if you have to target a platform prior to the ones specified below.
// Refer to MSDN for the latest info on corresponding values for different platforms.

#ifndef _WIN32_WINNT            // Specifies that the minimum required platform is Windows Vista.
#define _WIN32_WINNT 0x0600     // Change this to the appropriate value to target other versions of Windows.
#endif

#define _CRT_SECURE_NO_WARNINGS // disable useless warnings about "unsafe" string functions
#define _SCL_SECURE_NO_WARNINGS // disable useless warnings about "unsafe" iterators

#include "axl_g_Pch.h"

#include <new>
#include <typeinfo>

#include <stdint.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

#if (_AXL_ENV == AXL_ENV_WIN)
#	include <tchar.h>
#	include <winsock2.h>
#	include <ws2ipdef.h>
#	include <commctrl.h>

#	pragma comment (lib, "ws2_32.lib")
#	pragma comment (lib, "comctl32.lib")
#endif

//.............................................................................

// atl

#if (_AXL_ENV == AXL_ENV_WIN)
#	include <atlbase.h>
#	include <atlwin.h>
#endif

//.............................................................................

// LUA

extern "C" {

#include <lua.h>
#include <lualib.h>
#include <lauxlib.h>

} // extern "C" {

//.............................................................................

// libusb

#pragma warning (disable: 4200)
#include <libusb.h>

//.............................................................................

// openssl 

#include <openssl/ec.h>
#include <openssl/obj_mac.h>
#include <openssl/err.h>
#include <openssl/md5.h>
#include <openssl/ecdsa.h>

//.............................................................................

// axl

#define _AXL_DISABLE_PREMATURE_WINDOW_DESTRUCTION_CHECK

#include <axl_rtl_Array.h>
#include <axl_rtl_HashTable.h>
#include <axl_rtl_BoxList.h>
#include <axl_rtl_Packer.h>
#include <axl_rtl_Unpacker.h>
#include <axl_rtl_HandleTable.h>
#include <axl_rtl_Packetizer.h>
#include <axl_rtl_StringHashTable.h>
#include <axl_rtl_ForEach.h>
#include <axl_rtl_CmdLineParser.h>
#include <axl_rtl_BoyerMooreFind.h>
#include <axl_ref_WeakPtr.h>
#include <axl_ref_Child.h>
#include <axl_io_File.h>
#include <axl_io_MappedFile.h>
#include <axl_io_UsbDevice.h>
#include <axl_lex_RagelLexer.h>
#include <axl_lua_StringTemplate.h>
#include <axl_gui_GdiEngine.h>
#include <axl_ini_Parser.h>
#include <axl_enc_Base32Encoding.h>
#include <axl_g_Time.h>
#include <axl_cry_EcKey.h>
#include <axl_cry_EcPoint.h>

#if (_AXL_ENV == AXL_ENV_WIN)
#	include <axl_g_win_Window.h>
#endif

using namespace axl;

//.............................................................................