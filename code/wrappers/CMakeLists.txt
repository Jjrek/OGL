
target_include_directories( ${LIBRARY_BIN} PUBLIC include )
target_sources( ${LIBRARY_BIN} PUBLIC src/shader.cpp
                                        src/program.cpp
                                        src/window.cpp
                                        src/variable.cpp
                                        src/dataBuffer.cpp )
