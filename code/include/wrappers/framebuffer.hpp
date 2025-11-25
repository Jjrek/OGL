#ifndef INCLUDE_FRAMEBUFFER_HPP_
#define INCLUDE_FRAMEBUFFER_HPP_

#include <GL/glew.h>
#include <GL/gl.h>
#include <GLFW/glfw3.h>

namespace ogl {

	class Framebuffer{
			friend class ObjectFactory;
		private:

			///@brief Framebuffer id
			GLuint id;

			Framebuffer()noexcept;
			Framebuffer(const Framebuffer& old) = delete;
			Framebuffer(Framebuffer&& old) = delete;
			Framebuffer& operator=(const Framebuffer& old) = delete;
			Framebuffer& operator=(Framebuffer&& old) = delete;

		public:
			~Framebuffer();

			///@brief Function setting framebuffer as draw target
			void bind();

			///@brief Function setting default framebuffer as draw target
			static void bindDefault();
	};

}

#endif // INCLUDE_FRAMEBUFFER_HPP_
