#	OGL

Basic library managing OpenGL objects and providing user friendly API for data management.<br>
<br>

##	Dependencies

This library requires following to work properly:
 - OpenGL
 - GLEW
 - GLFW

and builds using *CMake* and *Make*.<br>
Additionally you need *Doxygen* if you wish to generate documentation.<br>
<br>

##	Compilation

To compile library run following command inside project directory:

	    mkdir build && cd build && cmake .. && make ogl

Compiling requires **CMake** and **Make** being installed.<br>
<br>

##	Documentation

To generate documentation run following inside build directory:

	    make docs

Folder '*docs*' will be created in repositorys **base folder**.<br>
Generating documentation requires **Doxygen**.<br>
<br>

##	Running example programs

To build and run provided example programs first run following in the build folder:

	    make examples && cd examples

Then you can run selected example program.<br>

