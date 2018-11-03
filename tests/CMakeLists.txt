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

if(ENABLE_SHARED)
	set(PROJECT_P503_LIBS p503)
	set(PROJECT_P751_LIBS p751)
else()
	set(PROJECT_P503_LIBS p503-static)
	set(PROJECT_P751_LIBS p751-static)
endif()

set(TESTER_SOURCES
	test_extras.c
	)

set(KAT_TESTER_SOURCES
	rng/rng.c
	aes/aes.c
	aes/aes_c.c
	)

# Copy KAT files in tester binary directory so they can run
file(COPY ../KAT DESTINATION ${CMAKE_CURRENT_BINARY_DIR})

if (ENABLE_P503)
	add_executable(arith_tests_p503_exe ${TESTER_SOURCES} arith_tests-p503.c)
	set_target_properties(arith_tests_p503_exe PROPERTIES OUTPUT_NAME arith_tests-p503)
	target_link_libraries(arith_tests_p503_exe PRIVATE ${PROJECT_P503_LIBS})
	add_test(NAME arith_p503 COMMAND arith_tests-p503)

	add_executable(test_SIDHp503_exe ${TESTER_SOURCES} test_SIDHp503.c)
	set_target_properties(test_SIDHp503_exe PROPERTIES OUTPUT_NAME test_SIDH-p503)
	target_link_libraries(test_SIDHp503_exe PRIVATE ${PROJECT_P503_LIBS})
	add_test(NAME SIDH_p503 COMMAND test_SIDH-p503)

	add_executable(test_SIKEp503_exe ${TESTER_SOURCES} test_SIKEp503.c)
	set_target_properties(test_SIKEp503_exe PROPERTIES OUTPUT_NAME test_SIKE-p503)
	target_link_libraries(test_SIKEp503_exe PRIVATE ${PROJECT_P503_LIBS})
	add_test(NAME SIKE_p503 COMMAND test_SIKE-p503)

	add_executable(PQCtestKAT_kem_p503_exe ${TESTER_SOURCES} ${KAT_TESTER_SOURCES} PQCtestKAT_kem503.c )
	set_target_properties(PQCtestKAT_kem_p503_exe PROPERTIES OUTPUT_NAME PQCtestKAT_kem-p503)
	target_link_libraries(PQCtestKAT_kem_p503_exe PRIVATE ${PROJECT_P503_LIBS})
	add_test(NAME KAT_p503 COMMAND PQCtestKAT_kem-p503)

endif()

if (ENABLE_P751)
	add_executable(arith_tests_p751_exe ${TESTER_SOURCES} arith_tests-p751.c)
	set_target_properties(arith_tests_p751_exe PROPERTIES OUTPUT_NAME arith_tests-p751)
	target_link_libraries(arith_tests_p751_exe PRIVATE ${PROJECT_P751_LIBS} ${PROJECT_P503_LIBS})
	add_test(NAME arith_p751 COMMAND arith_tests-p751)

	add_executable(test_SIDHp751_exe ${TESTER_SOURCES} test_SIDHp751.c)
	set_target_properties(test_SIDHp751_exe PROPERTIES OUTPUT_NAME test_SIDH-p751)
	target_link_libraries(test_SIDHp751_exe PRIVATE ${PROJECT_P751_LIBS} ${PROJECT_P503_LIBS})
	add_test(NAME SIDH_p751 COMMAND test_SIDH-p751)

	add_executable(test_SIKEp751_exe ${TESTER_SOURCES} test_SIKEp751.c)
	set_target_properties(test_SIKEp751_exe PROPERTIES OUTPUT_NAME test_SIKE-p751)
	target_link_libraries(test_SIKEp751_exe PRIVATE ${PROJECT_P751_LIBS} ${PROJECT_P503_LIBS})
	add_test(NAME SIKE_p751 COMMAND test_SIKE-p751)

	add_executable(PQCtestKAT_kem_p751_exe ${TESTER_SOURCES} ${KAT_TESTER_SOURCES} PQCtestKAT_kem751.c )
	set_target_properties(PQCtestKAT_kem_p751_exe PROPERTIES OUTPUT_NAME PQCtestKAT_kem-p751)
	target_link_libraries(PQCtestKAT_kem_p751_exe PRIVATE ${PROJECT_P751_LIBS})
	add_test(NAME KAT_p751 COMMAND PQCtestKAT_kem-p751)
endif()
