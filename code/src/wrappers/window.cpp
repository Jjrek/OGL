#include "wrappers/window.hpp"
#include "log.hpp"

#include <glm/glm.hpp>

#include <string>

namespace ogl {

	Window::Window(std::string title, glm::uvec2 size)noexcept{
		size_i = size;
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
		windowPtr = glfwCreateWindow(size.x, size.y, title.c_str(), nullptr, nullptr);
	}

	Window::~Window(){
		if(windowPtr){
			glfwDestroyWindow(windowPtr);
			windowPtr = nullptr;
		}
	}

	void Window::activate(){
		if(windowPtr){
			glfwMakeContextCurrent(windowPtr);
		}else{
			LOG(LogType::WRN)<<"Trying to activate invalid window\n";
		}
	}

	void Window::resize(glm::uvec2 size){
		size_i = size;
		glViewport(0, 0, size.x, size.y);
	}

	void Window::swap(){
		if(windowPtr){
			glfwSwapBuffers(windowPtr);
		}else{
			LOG(LogType::WRN)<<"Trying to swap invalid window\n";
		}
	}
}
