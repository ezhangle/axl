#..............................................................................

# aligned variable list printing helpers

macro (
axl_calc_max_string_length
	_RESULT
	# ...
	)

	set (_STRING_LIST ${ARGN})

	set (_MAX_LENGTH 0)
	foreach (_STRING ${_STRING_LIST})
		string (LENGTH ${_STRING} _LENGTH)
		if (${_LENGTH} GREATER ${_MAX_LENGTH})
			set (_MAX_LENGTH ${_LENGTH})
		endif ()
	endforeach ()

	set (${_RESULT} ${_MAX_LENGTH})
endmacro ()

macro (
axl_create_space_padding
	_RESULT
	_STRING
	_MAX_LENGTH
	)

	string (LENGTH ${_STRING} _LENGTH)
	math (EXPR _PADDING_LENGTH "${_MAX_LENGTH} - ${_LENGTH} + 1")

	if (${_PADDING_LENGTH} GREATER "0")
		string (RANDOM LENGTH ${_PADDING_LENGTH} ALPHABET " " _PADDING)
	else ()
		set (_PADDING " ")
	endif ()

	set (${_RESULT} ${_PADDING})
endmacro ()

macro (
axl_print_variable_list
	_INDENT
	_MIN_ALIGN
	# ...
	)

	set (_VARIABLE_LIST ${ARGN})

	axl_calc_max_string_length (_ALIGN ${_VARIABLE_LIST})

	string (LENGTH ${_INDENT} _INDENT_LENGTH)
	math (EXPR _ALIGN "${_ALIGN} + ${_INDENT_LENGTH} + 1")

	if (${_ALIGN} LESS ${_MIN_ALIGN})
		set (_ALIGN ${_MIN_ALIGN})
	endif ()

	foreach (_VARIABLE ${_VARIABLE_LIST})
		set (_PREFIX "${_INDENT}${_VARIABLE}:")
		axl_create_space_padding (_PADDING ${_PREFIX} ${_ALIGN})
		message(STATUS "${_PREFIX}${_PADDING}${${_VARIABLE}}")
	endforeach ()
endmacro ()

macro (
axl_filter_list
	_RESULT
	_FILTER
	# ...
	)

	set (_LIST ${ARGN})
	unset (_FILTERED_LIST)

	foreach (_ITEM ${_LIST})
		string (REGEX MATCH "${_FILTER}$" _MATCH "${_ITEM}")
		if (_MATCH)
			list (APPEND _FILTERED_LIST ${_ITEM})
		endif ()
	endforeach ()

	set (${_RESULT} ${_FILTERED_LIST})
endmacro ()

# when we don't know all the items on the list in advance,
# the best we can do is to align it on a constant column offset

set (AXL_G_MESSAGE_ALIGN 16) # adjustable

macro (
axl_message
	_PREFIX
	_SUFFIX
	)

	axl_create_space_padding (_PADDING ${_PREFIX} ${AXL_G_MESSAGE_ALIGN})
	message (STATUS "${_PREFIX}${_PADDING}${_SUFFIX}")
endmacro ()

#..............................................................................

# create a template file in form
#
# set (SETTING1 SETTING1-NOTFOUND)
# set (SETTING2 SETTING2-NOTFOUND)
# ...
#

macro (
	axl_create_empty_setting_file
	_FILE_NAME
	# ...
	)

	set (_SETTING_LIST ${ARGN})

	axl_calc_max_string_length (_MAX_LENGTH ${_SETTING_LIST})

	set (_CONTENTS "#\n")
	set (_CONTENTS "${_CONTENTS}# This is an auto-generated setting file\n")
	set (_CONTENTS "${_CONTENTS}# Fill it by hand with proper settings\n")
	set (_CONTENTS "${_CONTENTS}#\n\n")

	foreach (_SETTING ${_SETTING_LIST})
		axl_create_space_padding (_PADDING ${_SETTING} ${_MAX_LENGTH})
		set (_CONTENTS "${_CONTENTS}set (${_SETTING}${_PADDING}${_SETTING}-NOTFOUND)\n")
	endforeach ()

	file (WRITE ${_FILE_NAME} ${_CONTENTS})
endmacro ()

#..............................................................................

# detect host CPU (currently we only care support x86 and amd64)

macro (
axl_detect_cpu
	_CPU
	)

	if (CMAKE_SIZEOF_VOID_P EQUAL 8)
		set (${_CPU} "amd64")
	else ()
		set (${_CPU} "x86")
	endif ()
endmacro ()

#..............................................................................

# push and pop variables on stack

set (_AXL_G_STACK)

macro (
axl_push
	_VALUE
	)

	list (INSERT _AXL_G_STACK 0 ${_VALUE})
endmacro ()

macro (
axl_pop
	_RESULT
	)

	list (GET _AXL_G_STACK 0 ${_RESULT})
	list (REMOVE_AT _AXL_G_STACK 0)
endmacro ()

macro (
axl_push_and_set
	_VARIABLE
	_VALUE
	)

	axl_push (${${_VARIABLE}})
	set (${_VARIABLE} ${_VALUE})
endmacro ()

#..............................................................................

# cache setting with list of options

macro (
axl_create_setting
	_SETTING
	# ...
	)

	set (_ARG_LIST ${ARGN})

	set (_DESCRIPTION "${_SETTING}")
	set (_DEFAULT_VALUE)
	set (_TYPE STRING)
	set (_OPTION_LIST)
	set (_STATE "OPTIONS")

	foreach (_ARG ${_ARG_LIST})
		string (REGEX MATCH "TYPE|DESCRIPTION|DEFAULT|OPTIONS" _MATCH ${_ARG})

		if (NOT "${_MATCH}" STREQUAL "")
			set (_STATE ${_MATCH})
		elseif ("${_STATE}" STREQUAL "TYPE")
			set (_TYPE ${_ARG})
			set (_STATE "OPTIONS")
		elseif ("${_STATE}" STREQUAL "DESCRIPTION")
			set (_DESCRIPTION ${_ARG})
			set (_STATE "OPTIONS")
		elseif ("${_STATE}" STREQUAL "DEFAULT")
			set (_DEFAULT_VALUE ${_ARG})
			set (_STATE "OPTIONS")
		else ()
			set (_OPTION_LIST ${_OPTION_LIST} ${_ARG})
		endif ()
	endforeach ()

	if ("${${_SETTING}}" STREQUAL "")
		set (_FORCE FORCE)
	else ()
		set (_FORCE)
	endif ()

	set (
		${_SETTING} ${_DEFAULT_VALUE}
		CACHE ${_TYPE} ${_DESCRIPTION} ${_FORCE}
		)

	if (_OPTION_LIST)
		set_property (
			CACHE ${_SETTING}
			PROPERTY STRINGS
			${_OPTION_LIST}
			)
	endif ()
endmacro ()

macro (
axl_override_setting
	_SETTING
	# ...
	)

	set (_ARG_LIST ${ARGN})

	if (_ARG_LIST)
		list (GET _ARG_LIST 0 _VALUE)
	else ()
		set (_VALUE)
	endif ()

	get_property (
		_TYPE
		CACHE ${_SETTING}
		PROPERTY TYPE
		)

	get_property (
		_DESCRIPTION
		CACHE ${_SETTING}
		PROPERTY HELPSTRING
		)

	if ("${_TYPE}" STREQUAL "" OR "${_DESCRIPTION}" STREQUAL "")
		message (FATAL_ERROR "${_SETTING} is not a cached setting")
	endif ()

	set (
		${_SETTING} ${_VALUE}
		CACHE ${_TYPE} ${_DESCRIPTION} FORCE
		)
endmacro ()

macro (
axl_override_setting_once
	_SETTING
	# ...
	)

	if ("${${_SETTING}_OVERRIDEN}" STREQUAL "")
		axl_override_setting (${_SETTING} ${ARGN})

		set (
			${_SETTING}_OVERRIDEN TRUE
			CACHE INTERNAL "${_SETTING} is overriden"
			)
	endif ()
endmacro ()

#..............................................................................

# compiler flag settings (represented by mutually exclusive options in CMAKE_C/CXX_FLAGS)

# global list (users can add their own configurable settings here)

set (_AXL_G_COMPILER_FLAG_SETTING_LIST)

macro (
axl_create_compiler_flag_setting
	_SETTING
	# ...
	)

	set (_ARG_LIST ${ARGN})

	set (_DESCRIPTION "${_SETTING}")
	set (_DEFAULT_VALUE)
	set (_OPTION_LIST)
	set (_STATE "OPTIONS")

	foreach (_ARG ${_ARG_LIST})
		string (REGEX MATCH "DESCRIPTION|DEFAULT|OPTIONS" _MATCH ${_ARG})

		if (NOT "${_MATCH}" STREQUAL "")
			set (_STATE ${_MATCH})
		elseif ("${_STATE}" STREQUAL "DESCRIPTION")
			set (_DESCRIPTION ${_ARG})
			set (_STATE "OPTIONS")
		elseif ("${_STATE}" STREQUAL "DEFAULT")
			set (_DEFAULT_VALUE ${_ARG})
			set (_STATE "OPTIONS")
		else ()
			set (_OPTION_LIST ${_OPTION_LIST} ${_ARG})
		endif ()
	endforeach ()

	if (NOT "${${_SETTING}}" STREQUAL "") # setting is already defined (probably, via settings.cmake)
		set (_VALUE ${${_SETTING}})
	elseif (NOT "${_DEFAULT_VALUE}" STREQUAL "")
		set (_VALUE ${_DEFAULT_VALUE})
	else ()
		axl_get_compiler_flag_setting_current_value (_VALUE ${_SETTING} ${_OPTION_LIST})
	endif ()

	set (
		${_SETTING} ${_VALUE}
		CACHE STRING ${_DESCRIPTION}
		)

	set_property (
		CACHE ${_SETTING}
		PROPERTY STRINGS
		" " ${_OPTION_LIST}
		)

	list (APPEND _AXL_G_COMPILER_FLAG_SETTING_LIST ${_SETTING})
endmacro ()

macro (
axl_delete_compiler_flag_setting
	_SETTING
	)

	list (REMOVE_ITEM _AXL_G_COMPILER_FLAG_SETTING_LIST ${_SETTING})
endmacro ()

macro (
axl_get_compiler_flag_setting_current_value
	_RESULT
	_SETTING
	# ...
	)

	axl_create_compiler_flag_regex (_REGEX ${ARGN})

	axl_get_compiler_flag_setting_traits (
		${_SETTING}
		_CONFIGURATION_SUFFIX
		_IS_C_ONLY
		_IS_CPP_ONLY
		)

	if (_IS_C_ONLY)
		if ("${_CONFIGURATION_SUFFIX}" STREQUAL "")
			set (_FLAGS CMAKE_C_FLAGS)
		else ()
			set (_FLAGS CMAKE_C_FLAGS${_CONFIGURATION_SUFFIX})
		endif ()
	else ()
		if ("${_CONFIGURATION_SUFFIX}" STREQUAL "")
			set (_FLAGS CMAKE_CXX_FLAGS)
		else ()
			set (_FLAGS CMAKE_CXX_FLAGS${_CONFIGURATION_SUFFIX})
		endif ()
	endif ()

	string (REGEX MATCH ${_REGEX} _MATCH " ${${_FLAGS}} ")
	string (STRIP "${_MATCH}" ${_RESULT})
endmacro ()

macro (
axl_get_compiler_flag_setting_traits
	_SETTING
	_CONFIGURATION_SUFFIX_RESULT
	_IS_C_ONLY_RESULT
	_IS_CPP_ONLY_RESULT
	)

	# check whether this setting is per-configuration

	set (_CONFIGURATION_SUFFIX)

	string (TOUPPER "${_SETTING}" _SETTING_UC)

	foreach (_CONFIGURATION ${CMAKE_CONFIGURATION_TYPES})
		string (TOUPPER "${_CONFIGURATION}" _CONFIGURATION_UC)
		string (REGEX MATCH "_${_CONFIGURATION_UC}$" _MATCH "${_SETTING}")

		if (NOT "${_MATCH}" STREQUAL "")
			set (_CONFIGURATION_SUFFIX "_${_CONFIGURATION_UC}")
			break ()
		endif ()
	endforeach ()

	# check whether this setting is C-only

	string (REGEX MATCH "_C_" _MATCH "${_SETTING}")
	if (NOT "${_MATCH}" STREQUAL "")
		set (_IS_C_ONLY TRUE)
	else ()
		set (_IS_C_ONLY FALSE)
	endif ()

	# check whether this setting is C++-only

	string (REGEX MATCH "_CPP_|_CXX_" _MATCH "${_SETTING}")
	if (NOT "${_MATCH}" STREQUAL "")
		set (_IS_CPP_ONLY TRUE)
	else ()
		set (_IS_CPP_ONLY FALSE)
	endif ()

	set (${_CONFIGURATION_SUFFIX_RESULT} ${_CONFIGURATION_SUFFIX})
	set (${_IS_C_ONLY_RESULT} ${_IS_C_ONLY})
	set (${_IS_CPP_ONLY_RESULT} ${_IS_CPP_ONLY})
endmacro ()

macro (
axl_apply_compiler_flag_setting
	_SETTING
	)

	# create regex from option list and

	get_property (
		_OPTION_LIST
		CACHE ${_SETTING}
		PROPERTY STRINGS
		)

	if (NOT _OPTION_LIST)
		message (FATAL_ERROR "${_SETTING} does not have an associated option list")
	endif ()

	axl_create_compiler_flag_regex (_REGEX ${_OPTION_LIST})

	axl_get_compiler_flag_setting_traits (
		${_SETTING}
		_CONFIGURATION_SUFFIX
		_IS_C_ONLY
		_IS_CPP_ONLY
		)

	# apply current setting value to C/C++ flags

	if (NOT _IS_CPP_ONLY)
		if (NOT "${_CONFIGURATION_SUFFIX}" STREQUAL "")
			axl_apply_compiler_flag (
				CMAKE_C_FLAGS
				${_REGEX}
				)
		endif ()

		axl_apply_compiler_flag (
			CMAKE_C_FLAGS${_CONFIGURATION_SUFFIX}
			${_REGEX}
			${${_SETTING}}
			)
	endif ()

	if (NOT _IS_C_ONLY)
		if (NOT "${_CONFIGURATION_SUFFIX}" STREQUAL "")
			axl_apply_compiler_flag (
				CMAKE_CXX_FLAGS
				${_REGEX}
				)
		endif ()

		axl_apply_compiler_flag (
			CMAKE_CXX_FLAGS${_CONFIGURATION_SUFFIX}
			${_REGEX}
			${${_SETTING}}
			)
	endif ()
endmacro ()

macro (
axl_apply_all_compiler_flag_settings)
	foreach (_SETTING ${_AXL_G_COMPILER_FLAG_SETTING_LIST})
		axl_apply_compiler_flag_setting (${_SETTING})
	endforeach ()
endmacro ()

# direct management of individual flags

macro (
axl_create_compiler_flag_regex
	_RESULT
	# ...
	)

	set (_OPTION_LIST ${ARGN})

	set (_REGEX "")

	foreach (_OPTION ${_OPTION_LIST})
		string (STRIP ${_OPTION} _OPTION)
		if (NOT "${_OPTION}" STREQUAL "")
			string (REPLACE "+" "%+" _OPTION ${_OPTION}) # e.g. -std=c++0x
			set (_OPTION_REGEX " +${_OPTION} +")

			if ("${_REGEX}" STREQUAL "")
				set (_REGEX ${_OPTION_REGEX})
			else ()
				set (_REGEX "${_REGEX}|${_OPTION_REGEX}")
			endif ()
		endif ()
	endforeach ()

	set (${_RESULT} ${_REGEX})
endmacro ()

macro (
axl_apply_compiler_flag
	_RESULT
	_REGEX
	# ... _VALUE
	)

	set (_ARG_LIST ${ARGN})
	if (_ARG_LIST)
		list (GET _ARG_LIST 0 _VALUE)
	else ()
		set (_VALUE)
	endif ()

	set (_FLAGS ${${_RESULT}})

	# first, remove

	string (
		REGEX REPLACE
		"${_REGEX}"
		" "
		_FLAGS
		" ${_FLAGS} " # surround with spaces
		)

	string (STRIP "${_FLAGS}" _FLAGS)

	# now, if value is not empty, add it

	string (STRIP "${_VALUE}" _VALUE)

	if (NOT "${_VALUE}" STREQUAL "")
		set (_FLAGS "${_FLAGS} ${_VALUE}")
	endif ()


	set (${_RESULT} ${_FLAGS})
endmacro ()

#..............................................................................

# precompiled headers

macro (
axl_set_pch_msvc
	_TARGET
	_PCH_H
	_PCH_CPP
	)

	get_filename_component (_PCH_NAME ${_PCH_H} NAME_WE)
	set (_PCH_BIN "${CMAKE_CURRENT_BINARY_DIR}/${_TARGET}.dir/$(Configuration)/${_PCH_NAME}.pch")

	set_property (
		TARGET ${_TARGET}
		APPEND_STRING
		PROPERTY COMPILE_FLAGS
		" /Yu\"${_PCH_H}\" /Fp\"${_PCH_BIN}\""
		)

	set_property (
		SOURCE ${_PCH_CPP}
		APPEND_STRING
		PROPERTY COMPILE_FLAGS
		" /Yc\"${_PCH_H}\" /Fp\"${_PCH_BIN}\""
		)

	set_source_files_properties (
		${_PCH_CPP}
		PROPERTIES
		OBJECT_OUTPUTS "${_PCH_BIN}"
		)
endmacro ()

macro (
axl_append_compile_flag_list
	_FLAGS
	_PREFIX
	# ...
	)

	set (_ARG_LIST ${ARGN})

	foreach (_ARG ${_ARG_LIST})
		if (_ARG)
			if ("${_PREFIX}" STREQUAL "-I" AND ${_ARG} MATCHES "\\.framework/?$")
				string(REGEX REPLACE "/[^/]+\\.framework" "" _FRAMEWORK "${_ARG}")
				list (APPEND ${_FLAGS} "-F${_FRAMEWORK}")
			else ()
				list (APPEND ${_FLAGS} "${_PREFIX}${_ARG}")
			endif ()
		endif ()
	endforeach ()
endmacro ()

macro (
axl_set_pch_gcc
	_TARGET
	_PCH_CPP
	# ...
	)

	set (_EXTRA_FLAG_LIST ${ARGN})

	# select file paths: we need to generate a force-included header
	# in binary directory and precompiled header binary *NEXT* to it

	set (_PCH_H "${CMAKE_CURRENT_BINARY_DIR}/${_PCH_CPP}.h")
	set (_PCH_BIN "${CMAKE_CURRENT_BINARY_DIR}/${_PCH_CPP}.h.gch")

	# choose compiler and language by extension

	get_filename_component (_EXT ${_PCH_CPP} EXT)

	if ("${_EXT}" STREQUAL ".c")
		set (_COMPILER ${CMAKE_C_COMPILER})
		set (_PCH_FLAGS "-x" "c-header")
		set (_LANGUAGE "C")
	else ()
		set (_COMPILER ${CMAKE_CXX_COMPILER})
		set (_PCH_FLAGS "-x" "c++-header")
		set (_LANGUAGE "CXX")
	endif ()

	# start with compile flags global variables

	string (TOUPPER "${CMAKE_BUILD_TYPE}" _CONFIGURATION)

	set (_COMPILE_FLAGS "${CMAKE_${_LANGUAGE}_FLAGS} ${CMAKE_${_LANGUAGE}_FLAGS_${_CONFIGURATION}}")

	# get and append COMPILE_FLAGS property

	get_directory_property (_DIR_FLAGS COMPILE_FLAGS)
	get_target_property (_TARGET_FLAGS ${_TARGET} COMPILE_FLAGS)

	if (_DIR_FLAGS)
		set (_COMPILE_FLAGS "${_COMPILE_FLAGS} ${_DIR_FLAGS}")
	endif ()

	if (_TARGET_FLAGS)
		set (_COMPILE_FLAGS "${_COMPILE_FLAGS} ${_TARGET_FLAGS}")
	endif ()

	# turn it into a list

	string (STRIP "${_COMPILE_FLAGS}" _COMPILE_FLAGS)
	string (REGEX REPLACE " +" ";" _COMPILE_FLAGS "${_COMPILE_FLAGS}")

	# get and append COMPILE_DEFINITIONS property

	get_directory_property (_DIR_FLAGS COMPILE_DEFINITIONS)
	get_directory_property (_DIR_FLAGS_2 COMPILE_DEFINITIONS_${_CONFIGURATION})
	get_target_property (_TARGET_FLAGS ${_TARGET} COMPILE_DEFINITIONS)
	get_target_property (_TARGET_FLAGS_2 ${_TARGET} COMPILE_DEFINITIONS_${_CONFIGURATION})

	axl_append_compile_flag_list (
		_COMPILE_FLAGS
		"-D"
		${_DIR_FLAGS}
		${_DIR_FLAGS_2}
		${_TARGET_FLAGS}
		${_TARGET_FLAGS_2}
		)

	# add -isysroot on MacOS

	if (APPLE AND NOT "${CMAKE_OSX_SYSROOT}" STREQUAL "")
		list (
			APPEND
			_COMPILE_FLAGS
			"-isysroot"
			"${CMAKE_OSX_SYSROOT}"
			)
	endif ()

	# get and append INCLUDE_DIRECTORIES property

	get_directory_property (_DIR_FLAGS INCLUDE_DIRECTORIES)
	get_target_property (_TARGET_FLAGS ${_TARGET} INCLUDE_DIRECTORIES)

	axl_append_compile_flag_list (
		_COMPILE_FLAGS
		"-I"
		${_DIR_FLAGS}
		${_TARGET_FLAGS}
		)

	# append extra flags passed in vararg and finalize list

	if (_EXTRA_FLAG_LIST)
		list (APPEND _COMPILE_FLAGS "${_EXTRA_FLAG_LIST}")
	endif ()

	list (REMOVE_DUPLICATES _COMPILE_FLAGS)

	# create pch source file and custom command to build pch binary

	file (
		WRITE ${_PCH_H}
		"\#include \"${CMAKE_CURRENT_SOURCE_DIR}/${_PCH_CPP}\"\n"
		)

	add_custom_command (
		OUTPUT ${_PCH_BIN}
		MAIN_DEPENDENCY ${_PCH_CPP}
		COMMAND
			${_COMPILER}
			${_COMPILE_FLAGS}
			${_PCH_FLAGS}
			"-o" ${_PCH_BIN}
			${_PCH_H}
		)

	# modify target

	target_include_directories (
		${_TARGET}
		PUBLIC
		${CMAKE_CURRENT_BINARY_DIR}
		)

	set_property (
		TARGET ${_TARGET}
		APPEND_STRING
		PROPERTY COMPILE_FLAGS
		" -include \"${_PCH_H}\""
		)

	# add dependencies between target and pch binary

	add_custom_target (
		${_TARGET}_pch
		DEPENDS ${_PCH_BIN}
		)

	add_dependencies (${_TARGET} ${_TARGET}_pch)
endmacro ()

macro (
axl_set_pch
	_TARGET
	_PCH_H
	_PCH_CPP
	)
	if (MSVC AND MSVC_USE_PCH)
		axl_set_pch_msvc (${_TARGET} ${_PCH_H} ${_PCH_CPP} ${ARGN})
	elseif (GCC AND GCC_USE_PCH)
		axl_set_pch_gcc (${_TARGET} ${_PCH_CPP} ${ARGN})
	endif ()
endmacro ()

#..............................................................................

# exclude files from build (but keep it in project tree)

macro (
axl_set_header_file_only
	_IS_HEADER_FILE_ONLY
	# ...
	)

	set_source_files_properties (
		${ARGN}
		PROPERTIES
		HEADER_FILE_ONLY ${_IS_HEADER_FILE_ONLY}
		)
endmacro ()

macro (
axl_exclude_from_build
	# ...
	)

	axl_set_header_file_only (
		TRUE
		${ARGN}
		)
endmacro ()

macro (
axl_undo_exclude_from_build
	# ...
	)

	axl_set_header_file_only (
		FALSE
		${ARGN}
		)
endmacro ()

#..............................................................................

# file helpers

macro (
axl_find_executable
	_RESULT
	_FILE_NAME
	)

	if (WIN32)
		execute_process (
			COMMAND where ${_FILE_NAME}
			OUTPUT_VARIABLE _OUTPUT
			)

		string (REPLACE "\\" "/" _OUTPUT "${_OUTPUT}")
	else ()
		execute_process (
			COMMAND which ${_FILE_NAME}
			ERROR_FILE /dev/null
			OUTPUT_VARIABLE _OUTPUT
			)
	endif ()

	string (STRIP "${_OUTPUT}" _OUTPUT)

	if ("${_OUTPUT}" STREQUAL "")
		set (${_RESULT} ${_RESULT}-NOTFOUND)
	else ()
		set (${_RESULT} ${_OUTPUT})
	endif ()
endmacro ()

macro (
axl_find_inc_dir
	_RESULT
	_FILE_NAME
	)

	unset (_DIR)
	find_path (_DIR ${_FILE_NAME})

	if (NOT _DIR)
		set (${_RESULT} ${_RESULT}-NOTFOUND)
	elseif (WIN32)
		string (REPLACE "\\" "/" ${_RESULT} "${_DIR}")
	else ()
		set (${_RESULT} ${_DIR})
	endif ()

	unset (_DIR CACHE)
endmacro ()

macro (
axl_find_lib_dir
	_RESULT
	_LIB_NAME
	)

	unset (_PATH)
	find_library (_PATH ${_LIB_NAME})

	if (NOT _PATH)
		set (${_RESULT} ${_RESULT}-NOTFOUND)
	else ()
		if (WIN32)
			string (REPLACE "\\" "/" _PATH "${_PATH}")
		endif ()

		get_filename_component (
			_DIR
			${_PATH}
			DIRECTORY
			)

		set (${_RESULT} ${_DIR})
	endif ()

	unset (_PATH CACHE)
endmacro ()

macro (
axl_find_file
	_RESULT
	_FILE_NAME
	# ...
	)

	set (_DIR_LIST ${ARGN})

	set (_FILE_PATH ${_FILE_NAME}-NOTFOUND)

	foreach (_DIR ${_DIR_LIST})
		if (EXISTS ${_DIR}/${_FILE_NAME})
			set (_FILE_PATH ${_DIR}/${_FILE_NAME})
			break ()
		endif ()
	endforeach ()

	set (${_RESULT} ${_FILE_PATH})
endmacro ()

macro (
axl_find_file_recurse_parent_dirs
	_RESULT
	_FILE_NAME
	_START_DIR
	)

	set (_DIR ${_START_DIR})

	while (TRUE)
		if (EXISTS ${_DIR}/${_FILE_NAME})
			set (_FILE_PATH ${_DIR}/${_FILE_NAME})
			break ()
		endif ()

		get_filename_component (_PARENT_DIR "${_DIR}/.." ABSOLUTE)

		if (${_DIR} STREQUAL ${_PARENT_DIR})
			set (_FILE_PATH ${_FILE_NAME}-NOTFOUND)
			break ()
		endif ()

		set (_DIR ${_PARENT_DIR})
	endwhile ()

	set (${_RESULT} ${_FILE_PATH})
endmacro ()

macro (
axl_chain_include
	_FILE_NAME
	)

	axl_find_file_recurse_parent_dirs (_FILE_PATH ${_FILE_NAME} ${CMAKE_CURRENT_LIST_DIR}/..)

	if (_FILE_PATH)
		include (${_FILE_PATH})
	endif ()
endmacro ()

macro (
axl_make_path
	_FILE_PATH
	_FILE_NAME
	_BASE_DIR
	)

	if (IS_ABSOLUTE ${_FILE_NAME})
		set (${_FILE_PATH} ${_FILE_NAME})
	else ()
		set (${_FILE_PATH} "${_BASE_DIR}/${_FILE_NAME}")
	endif ()

endmacro ()

macro (
axl_ensure_file_exists
	_FILE_PATH
	_TEMPLATE_FILE_PATH
	)
	if (NOT EXISTS ${_FILE_PATH})
		file (READ ${_TEMPLATE_FILE_PATH} _BUFFER)
		file (WRITE ${_FILE_PATH} ${_BUFFER})
	endif ()
endmacro ()

macro (
axl_copy_file_if_different
	_TARGET
	_SRC_FILE_NAME
	_DST_FILE_NAME
	)

	add_custom_command (
		TARGET ${_TARGET}
		POST_BUILD
		COMMAND ${CMAKE_COMMAND} -E copy_if_different
			"${_SRC_FILE_NAME}"
			"${_DST_FILE_NAME}"
		)
endmacro ()

macro (
axl_copy_file_list_if_different
	_TARGET
	_SRC_DIR
	_DST_DIR
	# ...
	)

	set (_FILE_NAME_LIST ${ARGN})

	foreach (_FILE_NAME ${_FILE_NAME_LIST})
		axl_copy_file_if_different (
			${_TARGET}
			${_SRC_DIR}/${_FILE_NAME}
			${_DST_DIR}/${_FILE_NAME}
			)
	endforeach ()
endmacro ()

macro (
axl_configure_file_w_permissions
	_SRC_FILE
	_DST_FILE
	# ...
	)

	set (_PERMISSION_LIST ${ARGN})
	set (_TMP_FILE ${CMAKE_CURRENT_BINARY_DIR}/tmp/${_DST_FILE})

	configure_file (${_SRC_FILE} ${_TMP_FILE})

	file (
		COPY ${_TMP_FILE}
		DESTINATION ${CMAKE_CURRENT_BINARY_DIR}
		FILE_PERMISSIONS ${_PERMISSION_LIST}
		)

	file (REMOVE ${_TMP_FILE})
endmacro ()

macro (
axl_enum_directories
	_RESULT
	_DIR
	)

	file (GLOB _FILE_LIST RELATIVE ${_DIR} ${_DIR}/*)
	set (_DIR_LIST)

	foreach (_FILE ${_FILE_LIST})
		if (IS_DIRECTORY ${_DIR}/${_FILE})
			LIST (APPEND _DIR_LIST ${_FILE})
		endif ()
	endforeach ()

	set (${_RESULT} ${_DIR_LIST})
endmacro ()

#..............................................................................

# imports -- CMake' find_package replacement with support for manual override

set (AXL_STD_IMPORT_DIR ${CMAKE_CURRENT_LIST_DIR})

macro (
axl_include_import_file
	_IMPORT
	_IS_OPTIONAL
	)

	set (${_IMPORT}_FOUND FALSE)
	unset (_IMPORT_FILE_PATH)

	# use AXL_IMPORT_DIR_LIST first (to allow overriding)

	foreach (_IMPORT_DIR ${AXL_IMPORT_DIR_LIST})
		unset (_IMPORT_FILE_PATH)

		if (EXISTS ${_IMPORT_DIR}/import_${_IMPORT}.cmake)
			set (_IMPORT_FILE_PATH ${_IMPORT_DIR}/import_${_IMPORT}.cmake)
			break ()
		endif ()
	endforeach ()

	# fallback to standard import_*.cmake

	if (NOT _IMPORT_FILE_PATH AND EXISTS ${AXL_STD_IMPORT_DIR}/import_${_IMPORT}.cmake)
		set (_IMPORT_FILE_PATH ${AXL_STD_IMPORT_DIR}/import_${_IMPORT}.cmake)
	endif ()

	if (_IMPORT_FILE_PATH)
		include (${_IMPORT_FILE_PATH})

		string (TOUPPER ${_IMPORT} _IMPORT_UC)
		if (NOT ${_IMPORT_UC}_FOUND AND NOT _IS_OPTIONAL)
			message (FATAL_ERROR "${_IMPORT} is required but not found, check paths.cmake")
		endif ()
	elseif (NOT _IS_OPTIONAL)
		message (FATAL_ERROR "import_${_IMPORT}.cmake not found (use AXL_IMPORT_DIR_LIST in dependencies.cmake)")
	endif ()
endmacro ()

macro (
axl_import
	#...
	)

	set (_IMPORT_LIST ${ARGN})
	set (_IS_OPTIONAL FALSE)

	foreach (_IMPORT ${_IMPORT_LIST})
		if ("${_IMPORT}" STREQUAL "REQUIRED")
			set (_IS_OPTIONAL FALSE)
		elseif ("${_IMPORT}" STREQUAL "OPTIONAL")
			set (_IS_OPTIONAL TRUE)
		else ()
			axl_include_import_file (
				${_IMPORT}
				_IS_OPTIONAL
				)
		endif ()
	endforeach ()
endmacro ()

#..............................................................................
