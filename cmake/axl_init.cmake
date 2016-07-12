#..............................................................................

if (POLICY CMP0020)
	# Automatically link Qt executables to qtmain.lib on Windows (OLD: OFF; NEW: ON)
	cmake_policy (SET CMP0020 OLD)
endif ()

if (POLICY CMP0043)
	# Ignore COMPILE_DEFINITIONS_<Config> properties (OLD: OFF; NEW: ON)
	cmake_policy (SET CMP0043 NEW)
endif ()

if (POLICY CMP0054)
	# Only interpret if() arguments as variables or keywords when unquoted (OLD: OFF; NEW: ON)
	cmake_policy (SET CMP0054 NEW)
endif ()

include (${CMAKE_CURRENT_LIST_DIR}/axl_utils.cmake)
include (${CMAKE_CURRENT_LIST_DIR}/axl_std_settings.cmake)

axl_create_std_settings ()

set (CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/lib/${CONFIGURATION_SUFFIX_0})
set (CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/bin/${CONFIGURATION_SUFFIX_0})
set (CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/bin/${CONFIGURATION_SUFFIX_0})

set (
	AXL_IMPORT_DIR_LIST
	${AXL_IMPORT_DIR_LIST}
	${CMAKE_CURRENT_LIST_DIR}
	)

enable_testing ()

#..............................................................................
