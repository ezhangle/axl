set (VERSION_MAJOR     5)
set (VERSION_MINOR     0)
set (VERSION_REVISION  1)
set (VERSION_TAG)

set (VERSION_FILE_SUFFIX "${VERSION_MAJOR}.${VERSION_MINOR}.${VERSION_REVISION}")

if (NOT "${VERSION_TAG}" STREQUAL "")
	set (VERSION_TAG_SUFFIX " ${VERSION_TAG}")
	set (VERSION_FILE_SUFFIX "${VERSION_FILE_SUFFIX}-${VERSION_TAG}")
else ()
	set (VERSION_TAG_SUFFIX)
endif ()

set (VERSION_COMPANY   "Tibbo Technology Inc")
set (VERSION_YEARS     "2007-2014")
