#include "pch.h"
#include "axl_mt_psx_Mutex.h"
#include "axl_err_Error.h"
#include "axl_g_Time.h"

namespace axl {
namespace mt {
namespace psx {

//.............................................................................

int
MutexAttr::getType () const
{
	int type = PTHREAD_MUTEX_NORMAL;
	::pthread_mutexattr_gettype (&m_attr, &type);
	return type;
}

bool
MutexAttr::setType (int type)
{
	int result = ::pthread_mutexattr_settype (&m_attr, type);
	return result == 0 ? true : err::fail (result);
}

//.............................................................................

bool
Mutex::lock (uint_t timeout)
{
	int result;

	switch (timeout)
	{
	case 0:
		result = ::pthread_mutex_trylock (&m_mutex);
		break;

	case -1:
		result = ::pthread_mutex_lock (&m_mutex);
		break;

	default:
		timespec ts = { 0 };
		g::getAbsTimespecFromTimeout (timeout, &ts);
		result = ::pthread_mutex_timedlock (&m_mutex, &ts);
	}

	return result == 0 ? true : err::fail (result);
}

//.............................................................................

} // namespace psx
} // namespace mt
} // namespace axl
