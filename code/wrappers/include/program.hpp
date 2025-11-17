#ifndef INCLUDE_PROGRAM_HPP_
#define INCLUDE_PROGRAM_HPP_

#include "GLInterface.hpp"
#include "shader.hpp"

#include <memory>
#include <vector>

namespace ogl{

	///@brief Wrapper class containing single OpenGL program
	class Program{
		private:
			bool isValid;

			std::unique_ptr<GLInterface> gl;
			GLuint id;
			GLuint vertexArrayID;

			Program() = delete;
			Program(const Program& old) = delete;
			Program(Program&& old) = delete;
			Program& operator=(const Program& old) = delete;
			Program& operator=(Program&& old) = delete;

		public:
			///@param interface - Interface for OpenGL calls.
			Program(std::unique_ptr<GLInterface> interface = std::make_unique<GL>())noexcept;
			~Program();
			operator bool(){return isValid;}

			///@brief Builds and links passed shaders into program.
			bool build(const std::vector<std::shared_ptr<Shader>>& shaders);

			///@brief Activates program.
			void use();
	};

}
#endif // INCLUDE_PROGRAM_HPP_
