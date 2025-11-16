
target_include_directories( ${LIBRARY_BIN} PUBLIC include )
target_sources( ${LIBRARY_BIN} PUBLIC src/ogl.cpp
                                        src/GLInterface.cpp
                                        src/log.cpp)
add_subdirectory( wrappers )
