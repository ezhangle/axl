#include "pch.h"
#include "axl_io_FileEnumerator.h"

namespace axl {
namespace io {

//.............................................................................

#if (_AXL_ENV == AXL_ENV_WIN)

bool
FileEnumerator::openDir (const char* dir)
{
	close ();
	m_nextFileName.clear ();

	sl::String_w fileName = dir;
	fileName.append (L"\\*.*");

	WIN32_FIND_DATA findData;
	m_h = ::FindFirstFileW (fileName, &findData);
	if (m_h == INVALID_HANDLE_VALUE)
		return err::failWithLastSystemError ();

	m_nextFileName = findData.cFileName;
	return true;
}

sl::String
FileEnumerator::getNextFileName ()
{
	if (!isOpen ())
		return sl::String ();

	sl::String fileName = m_nextFileName;

	WIN32_FIND_DATA findData;
	bool_t result = ::FindNextFileW (m_h, &findData);
	if (result)
		m_nextFileName = findData.cFileName;
	else
		m_nextFileName.clear ();

	return fileName;
}

#elif (_AXL_ENV == AXL_ENV_POSIX)

bool
FileEnumerator::openDir (const char* dir)
{
	close ();
	m_nextFileName.clear ();

	m_h = ::opendir (dir);
	if (!m_h)
		return err::failWithLastSystemError ();

	dirent dirEntry;
	dirent* dirEntryPtr;
	int result = readdir_r (m_h, &dirEntry, &dirEntryPtr);
	
	if (result != 0)
		return err::failWithLastSystemError ();

	if (dirEntryPtr)
		m_nextFileName = dirEntryPtr->d_name;
	
	return true;
}

sl::String
FileEnumerator::getNextFileName ()
{
	if (!isOpen ())
		return sl::String ();

	sl::String fileName = m_nextFileName;

	dirent dirEntry;
	dirent* dirEntryPtr;
	int result = readdir_r (m_h, &dirEntry, &dirEntryPtr);
	
	if (result == 0 && dirEntryPtr)
		m_nextFileName = dirEntryPtr->d_name;
	else
		m_nextFileName.clear ();
	
	return fileName;
}

#endif

//.............................................................................

} // namespace io
} // namespace axl