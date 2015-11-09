#include "pch.h"
#include "axl_sl_BitMap.h"
#include "axl_sl_BitIdx.h"

namespace axl {
namespace sl {

//.............................................................................

bool
getBit (
	const size_t* map,
	size_t pageCount,
	size_t bit)
{
	size_t page = bit / _AXL_PTR_BITNESS;
	if (page >= pageCount)
		return false;

	size_t mask = (size_t) 1 << (bit & (_AXL_PTR_BITNESS - 1));
	
	return (map [page] & mask) != 0;
}

bool
setBit (
	size_t* map,
	size_t pageCount,
	size_t bit,
	bool value
	)
{
	size_t page = bit / _AXL_PTR_BITNESS;
	if (page >= pageCount)
		return false;

	size_t* p = map + page;
	size_t mask = (size_t) 1 << (bit & (_AXL_PTR_BITNESS - 1));
	size_t old = *p;

	if (value)
		*p |= mask;
	else
		*p &= ~mask;

	return *p != old;
}

bool
setBitRange ( 
	size_t* map,
	size_t pageCount,
	size_t from,
	size_t to,
	bool value
	)
{
	bool hasChanged = false;

	size_t bitCount = pageCount * _AXL_PTR_BITNESS;

	if (from >= bitCount)
		return false;

	if (to > bitCount)
		to = bitCount;

	size_t pageIndex = from / _AXL_PTR_BITNESS;
	size_t* p = map + pageIndex;

	from -= pageIndex * _AXL_PTR_BITNESS;
	to -= pageIndex * _AXL_PTR_BITNESS;

	size_t mask;
	size_t old;

	if (value)
	{
		old = *p;

		if (to < _AXL_PTR_BITNESS)
		{
			mask = getBitmask (from, to);
			*p |= mask;
			return *p != old;
		}

		mask = getHiBitmask (from);
		*p |= mask;

		if (*p != old)
			hasChanged = true;

		to -= _AXL_PTR_BITNESS;
		p++;
	
		while (to >= _AXL_PTR_BITNESS)
		{
			if (*p != -1)
				hasChanged = true;

			*p = -1;
			to -= _AXL_PTR_BITNESS;
			p++;
		}

		if (to)
		{
			mask = getLoBitmask (to);
			old = *p;
			*p |= mask;

			if (*p != old)
				hasChanged = true;
		}
	}
	else
	{
		old = *p;

		if (to < _AXL_PTR_BITNESS)
		{
			mask = getBitmask (from, to);
			*p &= ~mask;
			return *p != old;
		}

		mask = getHiBitmask (from);
		*p &= ~mask;

		if (*p != old)
			hasChanged = true;

		to -= _AXL_PTR_BITNESS;
		p++;
	
		while (to >= _AXL_PTR_BITNESS)
		{
			if (*p != 0)
				hasChanged = true;

			*p = 0;
			to -= _AXL_PTR_BITNESS;
			p++;
		}

		if (to)
		{
			mask = getLoBitmask (to);
			old = *p;
			*p &= ~mask;

			if (*p != old)
				hasChanged = true;
		}
	}

	return hasChanged;
}

bool
mergeBitMaps ( 
	size_t* map,
	const size_t* map2,
	size_t pageCount,
	BitOpKind op
	)
{
	bool hasChanged = false;

	size_t old;

	size_t* p = map;
	size_t* end = p + pageCount;
	const size_t* p2 = map2;

	switch (op)
	{
	case BitOpKind_Or:
		for (; p < end; p++, p2++)
		{
			old = *p;
			*p |= *p2;
			if (*p != old)
				hasChanged = true;
		}

		break;

	case BitOpKind_And:
		{
			old = *p;
			*p &= *p2;
			if (*p != old)
				hasChanged = true;
		}

		break;

	case BitOpKind_Xor:
		{
			old = *p;
			*p ^= *p2;
			if (*p != old)
				hasChanged = true;
		}

		break;

	default:
		ASSERT (false);	
	}

	return hasChanged;
}

size_t 
findBit (
	const size_t* map,
	size_t pageCount,
	size_t from,
	bool value
	)
{
	size_t i = from / _AXL_PTR_BITNESS;
	if (i >= pageCount)
		return -1;

	const size_t* p = map + i;

	from -= i * _AXL_PTR_BITNESS;

	if (value)
	{
		size_t x = *p & getHiBitmask (from);

		if (x)
			return i * _AXL_PTR_BITNESS + getLoBitIdx (x);

		for (i++, p++; i < pageCount; i++, p++)
		{
			if (*p != 0)
				return i * _AXL_PTR_BITNESS + getLoBitIdx (*p);
		}
	}
	else
	{
		size_t x = ~*p & getHiBitmask (from);

		if (x)
			return i * _AXL_PTR_BITNESS + getLoBitIdx (x);

		for (i++, p++; i < pageCount; i++, p++)
		{
			if (*p != -1)
				return i * _AXL_PTR_BITNESS + getLoBitIdx (~*p);
		}
	}

	return -1;
}

//.............................................................................

bool
BitMap::create (size_t bitCount)
{
	bool result = setBitCount (bitCount);
	if (!result)
		return false;

	clear ();
	return true;
}

bool 
BitMap::setBitCount (size_t bitCount)
{
	size_t pageCount = bitCount / _AXL_PTR_BITNESS;
	if (bitCount & (_AXL_PTR_BITNESS - 1))
		pageCount++;

	return m_map.setCount (pageCount);
}

void 
BitMap::copy (const BitMap& src)
{
	size_t count = src.m_map.getCount ();
	m_map.setCount (count);
	memcpy (m_map, src.m_map, count * sizeof (size_t));
}

int
BitMap::cmp (const BitMap& src) const
{
	size_t count = m_map.getCount ();
	size_t count2 = src.m_map.getCount ();

	return 
		count < count2 ? -1 :
		count > count2 ? 1 :
		memcmp (m_map, src.m_map, count * sizeof (size_t));
}

bool 
BitMap::merge (
	const BitMap& bitMap2, 
	BitOpKind op
	)
{
	size_t pageCount = m_map.getCount ();
	size_t pageCount2 = bitMap2.m_map.getCount ();
	
	return sl::mergeBitMaps (m_map, bitMap2.m_map, AXL_MIN (pageCount, pageCount2), op);
}

bool
BitMap::mergeResize (
	const BitMap& bitMap2, 
	BitOpKind op
	)
{
	size_t pageCount2 = bitMap2.m_map.getCount ();
	size_t pageCount = m_map.ensureCount (pageCount2);

	return sl::mergeBitMaps (m_map, bitMap2.m_map, pageCount, op);
}

//.............................................................................

} // namespace sl
} // namespace axl