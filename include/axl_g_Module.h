// This file is part of AXL (R) Library
// Tibbo Technology Inc (C) 2004-2015. All rights reserved
// Author: Vladimir Gladkov

#pragma once

#define _AXL_G_MODULE_H

#include "axl_sl_List.h"
#include "axl_sys_Lock.h"
#include "axl_sl_CallOnce.h"
#include "axl_mem_Tracker.h"
#include "axl_ref_Ptr.h"

namespace axl {
namespace g {

//..............................................................................

struct SystemInfo
{
	size_t m_processorCount;
	size_t m_pageSize;
	size_t m_mappingAlignFactor;
};

//..............................................................................

class Finalizer
{
public:
	virtual
	void
	finalize () = 0;
};

//..............................................................................

class Module
{
protected:
	class FinalizerEntry: public sl::ListLink
	{
	public:
		ref::Ptr <Finalizer> m_finalizer;
	};

protected:
#ifdef _AXL_DEBUG
	const char* m_tag;
#endif

#if (_AXL_OS_WIN)
	HMODULE m_hModule;
#endif

	SystemInfo m_systemInfo;

	mem::Tracker m_memTracker;

	// finalizers

	sys::Lock m_finalizerListLock;
	sl::StdList <FinalizerEntry> m_finalizerList;

public:
	Module ();

	~Module ();

#if (_AXL_OS_WIN)
	HMODULE
	getModuleHandle ()
	{
		return m_hModule;
	}
#endif

	SystemInfo*
	getSystemInfo ()
	{
		return &m_systemInfo;
	}

	mem::Tracker*
	getMemTracker ()
	{
		return &m_memTracker;
	}

	bool
	addFinalizer (const ref::Ptr <Finalizer>& finalizer);
};

// . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .

AXL_SELECT_ANY Module g_module;

inline
Module*
getModule ()
{
	return &g_module;
}

//..............................................................................

} // namespace g
} // namespace axl
