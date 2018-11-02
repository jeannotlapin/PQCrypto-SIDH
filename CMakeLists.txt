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
include(GNUInstallDirs)

cmake_minimum_required(VERSION 3.0)

project(sidh VERSION 3.0.0 LANGUAGES C ASM)

set(SIDH_SO_VERSION 3)

option(ENABLE_P503 "support prime p503 field arithmetic." ON)
option(ENABLE_P751 "support prime p751 field arithmetic." ON)
option(ENABLE_SHARED "Build shared library." ON)
option(ENABLE_STATIC "Build static library." ON)
option(ENABLE_STRICT "Pass strict flags to the compiler" ON)
option(ENABLE_TESTS "Enable compilation of tests" ON)
option(ENABLE_OPTIMIZATIONS "Use assembler optimized code if available(for x86_64 and arm64 processors)" ON)
option(USE_MULX "When available use additional optimization" ON)
option(USE_ADDX "When available use additional optimization" ON)
option(EXTENDED_FLAGS "Add compilation flags -fwrapv -fomit-frame-pointer -march=native" OFF)

list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake")

if(${CMAKE_SYSTEM_PROCESSOR} MATCHES "x86_64") # x86_64
	message("Target architecture is x86_64")
	set(TARGET_ARCH "x86_64")
	add_definitions("-D_AMD64_")
	if(ENABLE_OPTIMIZATIONS)
		add_definitions("-D_FAST_")
		if (USE_MULX)
			add_definitions("-D_MULX_")
			if (USE_ADX) # is available only if MULX is enabled
				add_definitions("-D_ADX_")
			endif()
		endif()
	else()
		add_definitions("-D_GENERIC_")
	endif()
elseif(${CMAKE_SYSTEM_PROCESSOR} MATCHES "arch64") # shall be arm64 bits
	message("Target architecture is ARM64 bits")
	set(TARGET_ARCH_DIR arm64)
	add_definitions("-D_ARM64_")
	if(ENABLE_OPTIMIZATIONS)
		add_definitions("-D_FAST_")
		if (USE_MULX)
			add_definitions("-D_MULX_")
			if (USE_ADX) # is available only if MULX is enabled
				add_definitions("-D_ADX_")
			endif()
		endif()
	else()
		add_definitions("-D_GENERIC_")
	endif()
else() # nothing picked yet, stick to the
	if(${CMAKE_SYSTEM_PROCESSOR} MATCHES "arm") # is an arm 32 bits
		add_definitions("-D_ARM_")
	endif()
	message("Target architecture not specific: use the general portable and not optimized C code")
	set(TARGET_ARCH GENERIC)
	add_definitions("-D_GENERIC_")
endif()

if(NOT CPACK_GENERATOR AND NOT CMAKE_INSTALL_RPATH AND CMAKE_INSTALL_PREFIX)
	set(CMAKE_INSTALL_RPATH ${CMAKE_INSTALL_FULL_LIBDIR})
	message(STATUS "Setting install rpath to ${CMAKE_INSTALL_RPATH}")
endif()

add_definitions("-D__LINUX__")

include_directories(
	include
	src
	${CMAKE_CURRENT_BINARY_DIR}
)

set(SIDH_INCLUDE_DIRS
	${PROJECT_SOURCE_DIR}/include
)

set(STRICT_OPTIONS_C "${STRICT_OPTIONS_C}  -std=gnu99 -Wstrict-prototypes -Wno-error=strict-prototypes -ffunction-sections -fdata-sections -fomit-frame-pointer ")
if (ENABLE_STRICT)
	set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${STRICT_OPTIONS_C}")
endif()
if (EXTENDED_FLAGS)
	set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -fwrapv -march=native ")
endif()


add_subdirectory(include)
add_subdirectory(src)

if(ENABLE_TESTS)
	enable_testing()
	add_subdirectory(tests)
endif()

export(EXPORT ${EXPORT_TARGETS_NAME}Targets
	FILE "${CMAKE_CURRENT_BINARY_DIR}/SIDHTargets.cmake"
)

configure_file(cmake/SIDHConfig.cmake.in
	"${CMAKE_CURRENT_BINARY_DIR}/SIDHConfig.cmake"
	@ONLY
)
set(ConfigPackageLocation "${CMAKE_INSTALL_DATADIR}/${PROJECT_NAME}/cmake")
install(EXPORT ${EXPORT_TARGETS_NAME}Targets
	FILE SIDHTargets.cmake
	DESTINATION ${ConfigPackageLocation}
)
install(FILES
	"${CMAKE_CURRENT_BINARY_DIR}/SIDHConfig.cmake"
	DESTINATION ${ConfigPackageLocation}
)
