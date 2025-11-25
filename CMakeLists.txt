
cmake_minimum_required( VERSION 3.27.0 )
project( OGL )

#cmake setup
set( CMAKE_CXX_STANDARD 20 )
set( CMAKE_CXX_STANDARD_REQUIRED True )
set( CMAKE_BUILD_TYPE Release )
set( CMAKE_EXPORT_COMPILE_COMMANDS OFF )


#building library
find_package( OpenGL REQUIRED )
find_package( GLEW REQUIRED )
find_package( glfw3 3.3 REQUIRED )

set( CMAKE_CXX_CLANG_TIDY clang-tidy )
set( LIBRARY_BIN ogl )
add_library( ${LIBRARY_BIN} STATIC )
unset( CMAKE_CXX_CLANG_TIDY )
target_compile_options( ${LIBRARY_BIN} PUBLIC -Wall
                                                -Wextra
                                                -Wpedantic
                                                -Werror
                                                -O3 )
add_subdirectory( code )
target_include_directories( ${LIBRARY_BIN} PUBLIC ${OPENGL_INCLUDE_DIRS} )


#tests
add_subdirectory( tests EXCLUDE_FROM_ALL )
#examples
add_subdirectory( examples EXCLUDE_FROM_ALL )

#documentation
find_package( Doxygen )
if( Doxygen_FOUND )
    set( DOXYGEN_OUTPUT_DIRECTORY ../docs )
    set( DOXYGEN_WARN_IF_UNDOCUMENTED NO )
    doxygen_add_docs( docs code EXCLUDE_FROM_ALL )
else()
    message( WARNING "Doxygen not found! Skipping documentation generation" )
endif()

