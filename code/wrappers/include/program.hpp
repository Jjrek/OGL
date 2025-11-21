#ifndef INCLUDE_PROGRAM_HPP_
#define INCLUDE_PROGRAM_HPP_

#include "GLInterface.hpp"
#include "shader.hpp"
#include "variable.hpp"

#include <memory>
#include <vector>
#include <map>

namespace ogl{

	///@brief Wrapper class containing single OpenGL program
	class Program{
		private:
			bool isValid;

			std::shared_ptr<GLInterface> gl;
			GLuint id;
			GLuint vertexArrayID;

			std::map<std::string, std::shared_ptr<Variable>> variables;

			Program() = delete;
			Program(const Program& old) = delete;
			Program(Program&& old) = delete;
			Program& operator=(const Program& old) = delete;
			Program& operator=(Program&& old) = delete;

			void poll(GLenum resourceType, auto factory);
			void pollVariables();

		public:
			///@param interface - Interface for OpenGL calls.
			Program(std::shared_ptr<GLInterface> interface = std::make_unique<GL>())noexcept;
			~Program();
			operator bool(){return isValid;}

			///@brief Builds and links passed shaders into program.
			bool build(const std::vector<std::shared_ptr<Shader>>& shaders);

			///@brief Activates program.
			void use();

			///@brief Returns stored variable wrapper or empty pointer if not found.
			std::shared_ptr<Variable> get(std::string varName);
	};

}
#endif // INCLUDE_PROGRAM_HPP_
