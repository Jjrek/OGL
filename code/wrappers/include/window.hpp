#ifndef INCLUDE_WINDOW_HPP_
#define INCLUDE_WINDOW_HPP_

#include <GL/glew.h>
#include <GL/gl.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>

#include <string>

namespace ogl {

	class Window{
		private:
			GLFWwindow* windowPtr;
			glm::uvec2 size_i;

			Window(const Window& old) = delete;
			Window(Window&& old) = delete;
			Window& operator=(const Window& old) = delete;
			Window& operator=(Window&& old) = delete;

		public:
			Window(std::string title = "title", glm::uvec2 size = {480,320})noexcept;
			~Window();

			operator bool(){return windowPtr;}

			void activate();
			void swap();
			glm::uvec2 size(){return size_i;};
			void resize(glm::uvec2 size);
	};

}

#endif // INCLUDE_WINDOW_HPP_
