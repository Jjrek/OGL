#ifndef INCLUDE_SHADER_HPP_
#define INCLUDE_SHADER_HPP_

#include "GLInterface.hpp"

#include <memory>
#include <string>
#include <set>

namespace ogl{

	///@brief Wrapper class containing single OpenGL shader
	class Shader{
		private:
			std::string code_i;
			bool isValid;

			std::shared_ptr<GLInterface> gl;

			GLenum type;
			GLuint id_i;

			Shader() = delete;
			Shader(const Shader& old) = delete;
			Shader(Shader&& old) = delete;
			Shader& operator=(const Shader& old) = delete;
			Shader& operator=(Shader&& old) = delete;

			void Delete();

		public:
			using CompileFlags = std::set<std::string>;
			/**
			@param shaderType - Type of shader to create.
			@param rawCode - Code of shader to be processed and compiled.
			@param compileFlags - Flags defining blocks to keep when processing the shader\n
			Flags are case sensitive\n
			Flag blocks must start with '@' line, and end with "@!"
			followed by space or tab character.\n
			If block may be used by more than one keyword,
			identifiers must be separated by spaces or tabs\n
			\~ works as negation, works for single flag
			Example block:\n
			\@flag\n
			\@~flag1\n
			Code to be used only with flag and only without flag1\n
			\@!~flag1\n
			\@!flag\n
			Code to be used always\n
			\@randomname FLAG3\n
			Code to be used with randomname or FLAG3\n
			\@!randomname FLAG3\n
			@param interface - Interface for OpenGL calls.
			*/
			Shader( const GLenum shaderType,
					const std::string rawCode,
					const CompileFlags& compileFlags = {},
					std::shared_ptr<GLInterface> interface = std::make_shared<GL>())noexcept;
			virtual ~Shader();

			///@brief OpenGl shader id getter
			virtual GLuint id(){return id_i;};

			///@brief Returns code that was passed to OpenGL.
			std::string code(){return code_i;}
			operator bool(){return isValid;}
	};

}

#endif // INCLUDE_SHADER_HPP_
