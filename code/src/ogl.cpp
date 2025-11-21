#include "ogl.hpp"
#include "log.hpp"

#include <GL/glew.h>
#include <GL/gl.h>
#include <GLFW/glfw3.h>

#include <memory>

namespace ogl{

	Ogl::Ogl()noexcept{

		isValid = true;

		auto glfwErrorCallback = [](int error, const char* description){
			LOG(LogType::ERROR)<<"GLFW:"<<error<<": "<<description<<"\n";
		};
		glfwSetErrorCallback(glfwErrorCallback);

		if(!glfwInit()){
			isValid = false;
			LOG(LogType::ERROR)<<"Failed initializing glfw\n";
			return;
		}

		window_i = std::make_shared<Window>();
		if(!window_i){
			isValid = false;
			LOG(LogType::ERROR)<<"Failed creating window\n";
			return;
		}
		window_i->activate();

		glewExperimental = GL_TRUE;
		//ignoring 4 is workaround for known glew bug that happens on some systems
		if(GLenum error = glewInit(); error && error != 4){
			isValid = false;
			LOG(LogType::ERROR)<<"Failed initializing glew\n"
								<<"GLEW:"
								<<error
								<<": "
								<<glewGetErrorString(error)
								<<"\n";
		}
	}

	Ogl::~Ogl(){
		window_i.reset();
		glfwTerminate();
	}

}
