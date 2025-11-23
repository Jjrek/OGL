
find_package( GTest )
if( GTest_FOUND )
    set( TEST_BIN tests )
    add_executable( ${TEST_BIN} EXCLUDE_FROM_ALL )
	target_include_directories( ${TEST_BIN} PUBLIC include/
                                                    mocks/
                                                    ../code/include/)
	target_sources( ${TEST_BIN} PUBLIC setup.cpp
										logging.cpp
										shader.cpp
										program.cpp
										variable.cpp
										dataBuffer.cpp )
    target_link_libraries( ${TEST_BIN}  ${LIBRARY_BIN}
                                        GTest::gtest
                                        GTest::gtest_main
                                        GTest::gmock
                                        GTest::gmock_main
                                        ${OPENGL_LIBRARIES}
                                        ${GLEW_LIBRARIES}
                                        glfw)
else()
    message( WARNING "GTest not found! Skipping test generation" )
endif()

