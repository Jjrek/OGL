
set( EXAMPLES examples )
add_custom_target( ${EXAMPLES}  COMMAND rm -rf ${CMAKE_CURRENT_BINARY_DIR}/shaders/
                                COMMAND cp -r ${CMAKE_CURRENT_SOURCE_DIR}/shaders/ ${CMAKE_CURRENT_BINARY_DIR})
function(compileExample NAME )
    add_executable( ${NAME} ${NAME}.cpp )
    target_include_directories( ${NAME} PUBLIC ../code/include/
                                                 ${OPENGL_INCLUDE_DIRS}
                                                 ${GLEW_INCLUDE_DIRS} )
    target_link_libraries( ${NAME} ${LIBRARY_BIN}
                                    ${OPENGL_LIBRARIES}
                                    ${GLEW_LIBRARIES}
                                    glfw )
    add_dependencies( ${EXAMPLES} ${NAME} )
endfunction()

compileExample( 01-BasicTriangle )

