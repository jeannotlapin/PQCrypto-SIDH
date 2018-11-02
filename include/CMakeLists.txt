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
set(HEADER_FILES )
if(ENABLE_P503)
	set(HEADER_FILES ${HEADER_FILES}
		P503_api.h
	)
endif()
if(ENABLE_P751)
	set(HEADER_FILES ${HEADER_FILES}
		P751_api.h
	)
endif()

set(SIDH_HEADER_FILES )
foreach(HEADER_FILE ${HEADER_FILES})
	list(APPEND SIDH_HEADER_FILES "${CMAKE_CURRENT_LIST_DIR}/sidh/${HEADER_FILE}")
endforeach()
set(SIDH_HEADER_FILES ${SIDH_HEADER_FILES} PARENT_SCOPE)

install(FILES ${SIDH_HEADER_FILES}
        DESTINATION include/sidh
        PERMISSIONS OWNER_READ OWNER_WRITE GROUP_READ WORLD_READ)
