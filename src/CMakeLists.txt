############################################################################
# CMakeLists.txt
# Copyright (C) 2018  Johan Pascal
#
############################################################################
#
# MIT License
#
# Permission is hereby granted, free of charge, to any person obtaining a copy
# of this software and associated documentation files (the "Software"), to deal
# in the Software without restriction, including without limitation the rights
# to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
# copies of the Software, and to permit persons to whom the Software is
# furnished to do so, subject to the following conditions:
#
# The above copyright notice and this permission notice shall be included in all
# copies or substantial portions of the Software.
#
# THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
# IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
# FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
# AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
# LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
# OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
# SOFTWARE.
#
############################################################################
set(SIDH_C_INCLUDED_CODE
	ec_isogeny.c
	fpx.c
	sidh.c
	sike.c)

set(SIDH_C_SOURCE_FILES
	random/random.c
	sha3/fips202.c
)

set(SIDH_C_P503_SOURCE_FILES
	${SIDH_C_SOURCE_FILES}
	P503/P503.c
)

set(SIDH_C_P503_HEADER_FILES
	P503/P503_internal.h
	config.h
)

set(SIDH_C_P751_SOURCE_FILES
	${SIDH_C_SOURCE_FILES}
	P751/P751.c
)

set(SIDH_C_P751_HEADER_FILES
	P751/P751_internal.h
	config.h
)

if (TARGET_ARCH STREQUAL "x86_64" AND ENABLE_OPTIMIZATIONS)
	set(SIDH_C_P503_SOURCE_FILES
		${SIDH_C_P503_SOURCE_FILES}
		P503/AMD64/fp_x64.c
		P503/AMD64/fp_x64_asm.S
	)
	set(SIDH_C_P751_SOURCE_FILES
		${SIDH_C_P751_SOURCE_FILES}
		P751/AMD64/fp_x64.c
		P751/AMD64/fp_x64_asm.S
	)
elseif (TARGET_ARCH STREQUAL "arm64" AND ENABLE_OPTIMIZATIONS)
	set(SIDH_C_P503_SOURCE_FILES
		${SIDH_C_P503_SOURCE_FILES}
		P503/ARM64/fp_arm64.c
		P503/ARM64/fp_arm64_asm.S
	)
	set(SIDH_C_P751_SOURCE_FILES
		${SIDH_C_P751_SOURCE_FILES}
		P751/ARM64/fp_arm64.c
		P751/ARM64/fp_arm64_asm.S
	)
else()
	set(SIDH_C_P503_SOURCE_FILES
		${SIDH_C_P503_SOURCE_FILES}
		P503/generic/fp_generic.c
	)
	set(SIDH_C_P751_SOURCE_FILES
		${SIDH_C_P751_SOURCE_FILES}
		P751/generic/fp_generic.c
	)
endif()


if(ENABLE_STATIC)
	if(ENABLE_P503)
		add_library(p503-static STATIC ${SIDH_C_P503_SOURCE_FILES} ${SIDH_C_P503_HEADER_FILES})
		set_target_properties(p503-static PROPERTIES LINKER_LANGUAGE "C")
		set_target_properties(p503-static PROPERTIES OUTPUT_NAME p503)
	endif()
	if(ENABLE_P751)
		add_library(p751-static STATIC ${SIDH_C_P751_SOURCE_FILES} ${SIDH_C_P751_HEADER_FILES})
		set_target_properties(p751-static PROPERTIES LINKER_LANGUAGE "C")
		set_target_properties(p751-static PROPERTIES OUTPUT_NAME p751)
	endif()
endif()
if(ENABLE_SHARED)
	if(ENABLE_P503)
		add_library(p503 SHARED ${SIDH_C_P503_SOURCE_FILES} ${SIDH_C_P503_HEADER_FILES})
		set_target_properties(p503 PROPERTIES LINKER_LANGUAGE "C")
		set_target_properties(p503 PROPERTIES SOVERSION ${SIDH_SO_VERSION})
	endif()
	if(ENABLE_P751)
		add_library(p751 SHARED ${SIDH_C_P751_SOURCE_FILES} ${SIDH_C_P751_HEADER_FILES})
		set_target_properties(p751 PROPERTIES LINKER_LANGUAGE "C")
		set_target_properties(p751 PROPERTIES SOVERSION ${SIDH_SO_VERSION})
	endif()
endif()


if(ENABLE_STATIC)
	if(ENABLE_P503)
		install(TARGETS p503-static EXPORT ${EXPORT_TARGETS_NAME}Targets
			RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
			LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
			ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
			PERMISSIONS OWNER_READ OWNER_WRITE OWNER_EXECUTE GROUP_READ GROUP_EXECUTE WORLD_READ WORLD_EXECUTE
		)
	endif()
	if(ENABLE_P751)
		install(TARGETS p751-static EXPORT ${EXPORT_TARGETS_NAME}Targets
			RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
			LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
			ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
			PERMISSIONS OWNER_READ OWNER_WRITE OWNER_EXECUTE GROUP_READ GROUP_EXECUTE WORLD_READ WORLD_EXECUTE
		)
	endif()
endif()
if(ENABLE_SHARED)
	if(ENABLE_P503)
		install(TARGETS p503 EXPORT ${EXPORT_TARGETS_NAME}Targets
			RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
			LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
			ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
			PERMISSIONS OWNER_READ OWNER_WRITE OWNER_EXECUTE GROUP_READ GROUP_EXECUTE WORLD_READ WORLD_EXECUTE
		)
	endif()
	if(ENABLE_P751)
		install(TARGETS p751 EXPORT ${EXPORT_TARGETS_NAME}Targets
			RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
			LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
			ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
			PERMISSIONS OWNER_READ OWNER_WRITE OWNER_EXECUTE GROUP_READ GROUP_EXECUTE WORLD_READ WORLD_EXECUTE
		)
	endif()
endif()
