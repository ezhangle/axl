// This file is part of AXL (R) Library
// Tibbo Technology Inc (C) 2004-2014. All rights reserved
// Author: Vladimir Gladkov

#pragma once

#include "axl_rtl_List.h"
#include "axl_rtl_String.h"
#include "axl_io_SockAddr.h"

#define _AXL_IO_NETWORKADAPTER_H

namespace axl {
namespace io {

class NetworkAdapterEnumerator;

//.............................................................................

enum NetworkAdapterType
{
	NetworkAdapterType_Unknown,
	NetworkAdapterType_Loopback,
	NetworkAdapterType_Ethernet,
	NetworkAdapterType_Wireless,
	NetworkAdapterType_Ppp,
	NetworkAdapterType_TokenRing,
	NetworkAdapterType_Slip,
	NetworkAdapterType_Tunnel,
	NetworkAdapterType__Count,
};

//. . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .

const char* 
getNetworkAdapterTypeString (NetworkAdapterType adapterKind);

//.............................................................................

enum NetworkAdapterFlag
{
	NetworkAdapterFlag_Dhcp      = 0x01,
	NetworkAdapterFlag_Ddns      = 0x02,
	NetworkAdapterFlag_Broadcast = 0x04,
	NetworkAdapterFlag_Multicast = 0x08,
	NetworkAdapterFlag_Ip4       = 0x10,
	NetworkAdapterFlag_Ip6       = 0x20,
};

//. . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .

inline
NetworkAdapterFlag
getFirstNetworkAdapterFlag (uint_t flags)
{
	return (NetworkAdapterFlag) (1 << rtl::getLoBitIdx (flags));
}

const char* 
getNetworkAdapterFlagString (NetworkAdapterFlag flag);

rtl::String
getNetworkAdapterFlagString (uint_t flags);

//.............................................................................

struct NetworkAdapterAddress: rtl::ListLink
{
	SockAddr m_address;
	size_t m_netMaskBitCount;
};

//. . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .

class NetworkAdapterDesc: public rtl::ListLink
{
	friend class NetworkAdapterEnumerator;

protected:
	NetworkAdapterType m_type;
	uint_t m_flags;
	rtl::String m_name;
	rtl::String m_description;
	uchar_t m_mac [6];
	rtl::StdList <NetworkAdapterAddress> m_addressList;

public:
	NetworkAdapterDesc ();

	NetworkAdapterType 
	getType () const
	{
		return m_type;
	}
	
	uint_t 
	getFlags () const
	{
		return m_flags;
	}

	rtl::String 
	getName () const
	{
		return m_name;
	}

	rtl::String 
	getDescription () const
	{
		return m_description;
	}

	const uchar_t* 
	getMac () const
	{
		return m_mac;
	}

	rtl::ConstList <NetworkAdapterAddress> 
	getAddressList () const
	{
		return m_addressList;
	}
};

//. . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .

size_t
createNetworkAdapterDescList (rtl::StdList <NetworkAdapterDesc>* adapterList);

//.............................................................................

} // namespace io
} // namespace axl