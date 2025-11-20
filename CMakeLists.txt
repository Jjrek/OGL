
cmake_minimum_required( VERSION 3.27.0 )
project( OGL )

#cmake setup
set( CMAKE_CXX_STANDARD 20 )
set( CMAKE_CXX_STANDARD_REQUIRED True )
set( CMAKE_EXPORT_COMPILE_COMMANDS ON )

set( CMAKE_BUILD_TYPE Debug )
set( CMAKE_CXX_FLAGS "-Wall -Wextra -Wpedantic -Werror" )
set( CMAKE_CXX_FLAGS_RELEASE "-O3" )
set( CMAKE_CXX_FLAGS_DEBUG  "-O0 -g" )
if( CMAKE_BUILD_TYPE MATCHES Debug )
    add_compile_definitions( Debug )
endif()

set( CMAKE_CXX_CLANG_TIDY clang-tidy )


#building library
find_package( OpenGL REQUIRED )
find_package( GLEW REQUIRED )
find_package( glfw3 3.3 REQUIRED )
       

set( LIBRARY_BIN ogl )
add_library( ${LIBRARY_BIN} STATIC )
add_subdirectory( code )
target_include_directories( ${LIBRARY_BIN} PUBLIC ${OPENGL_INCLUDE_DIRS} ${GLEW_INCLUDE_DIRS} )


#utilities
if( CMAKE_BUILD_TYPE MATCHES Debug )
    #documentation
    find_package( Doxygen )
    if( Doxygen_FOUND )
        set( DOXYGEN_OUTPUT_DIRECTORY ../docs )
        set( DOXYGEN_WARN_IF_UNDOCUMENTED NO )
        doxygen_add_docs( docs code ALL )
    else()
        message( WARNING "Doxygen not found! Skipping documentation generation" )
    endif()

    #tests
    find_package( GTest )
    if( GTest_FOUND )
        set( TEST_BIN testRun )
        add_executable( ${TEST_BIN} )
        add_subdirectory( tests )
        target_include_directories( ${TEST_BIN} PUBLIC ./code/include/ ${OPENGL_INCLUDE_DIRS} ${GLEW_INCLUDE_DIRS} )
        target_link_libraries( ${TEST_BIN}  ${LIBRARY_BIN}
                                            GTest::gtest
                                            GTest::gtest_main
                                            GTest::gmock
                                            GTest::gmock_main
                                            ${OPENGL_LIBRARIES}
                                            ${GLEW_LIBRARIES}
                                            glfw )
    else()
        message( WARNING "GTest not found! Skipping test generation" )
    endif()
else()
    message( NOTICE "Non debug build. Skipping test and docs generation" )
endif()
