// This file is part of AXL (R) Library
// Tibbo Technology Inc (C) 2004-2014. All rights reserved
// Author: Vladimir Gladkov

#pragma once

#define _AXL_RTL_GUID_H

#include "axl_g_Def.h"

namespace axl {
namespace rtl {

template <typename T> class StringBase;
typedef StringBase <char> String;

//.............................................................................

enum GuidStringFlag
{
	GuidStringFlag_UpperCase   = 0x01,
	GuidStringFlag_CurlyBraces = 0x02,
};

//. . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .

struct Guid
{
	union
	{
		struct
		{
			uint32_t m_data1;
			uint16_t m_data2;
			uint16_t m_data3;
			uint8_t m_data4 [8];
		};

		struct
		{
			uint32_t m_long1;
			uint32_t m_long2;
			uint32_t m_long3;
			uint32_t m_long4;
		};

#if (_AXL_ENV == AXL_ENV_WIN)
		GUID m_guid;
#endif
	};

	bool
	operator == (const Guid& guid) const
	{
		return isEqual (guid);
	}

	bool
	operator != (const Guid& guid) const
	{
		return !isEqual (guid);
	}

	int
	cmp (const Guid& guid) const
	{
		return memcmp (this, &guid, sizeof (Guid));
	}

	bool
	isEqual (const Guid& guid) const
	{
		return
			m_long1 == guid.m_long1 &&
			m_long2 == guid.m_long2 &&
			m_long3 == guid.m_long3 &&
			m_long4 == guid.m_long4;
	}

	rtl::String
	getGuidString (uint_t flags = 0) const;

	void
	setup (
		uint32_t l,
		uint16_t s1,
		uint16_t s2,
		uint8_t b1,
		uint8_t b2,
		uint8_t b3,
		uint8_t b4,
		uint8_t b5,
		uint8_t b6,
		uint8_t b7,
		uint8_t b8
		)
	{
		m_data1 = l;
		m_data2 = s1;
		m_data3 = s2;
		m_data4 [0] = b1;
		m_data4 [1] = b2;
		m_data4 [2] = b3;
		m_data4 [3] = b4;
		m_data4 [4] = b5;
		m_data4 [5] = b6;
		m_data4 [6] = b7;
		m_data4 [7] = b8;
	}

	bool
	parse (const char* string);

	bool
	generate ();
};

//.............................................................................

inline
Guid
buildGuid (
	uint32_t l,
	uint16_t s1,
	uint16_t s2,
	uint8_t b1,
	uint8_t b2,
	uint8_t b3,
	uint8_t b4,
	uint8_t b5,
	uint8_t b6,
	uint8_t b7,
	uint8_t b8
	)
{
	Guid guid;
	guid.setup (l, s1, s2, b1, b2, b3, b4, b5, b6, b7, b8);
	return guid;
}

inline
Guid
parseGuid (const char* string)
{
	Guid guid;
	guid.parse (string);
	return guid;
}

inline
Guid
generateGuid ()
{
	Guid guid;
	guid.generate ();
	return guid;
}

//.............................................................................

// global GUIDs

#define AXL_RTL_GUID_INITIALIZER(l, s1, s2, b1, b2, b3, b4, b5, b6, b7, b8) \
	{ { { l, s1, s2, { b1, b2,  b3,  b4,  b5,  b6,  b7,  b8 } } } }

#define AXL_RTL_DEFINE_GUID(n, l, s1, s2, b1, b2, b3, b4, b5, b6, b7, b8) \
	extern AXL_SELECT_ANY const axl::rtl::Guid n = \
		AXL_RTL_GUID_INITIALIZER (l, s1, s2, b1, b2,  b3,  b4,  b5,  b6,  b7,  b8)

AXL_RTL_DEFINE_GUID (GUID_Null, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0);

//.............................................................................

} // namespace rtl
} // namespace axl
