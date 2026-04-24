#ifndef INCLUDE_OGL_SHADER_HPP_
#define INCLUDE_OGL_SHADER_HPP_

#include "GLInterface.hpp"

#include <memory>
#include <string>
#include <set>
#include <fstream>

namespace ogl{

	///@brief Wrapper class containing single OpenGL shader
	class Shader{
			friend class ObjectFactory;
		private:
			std::string code_i;
			bool isValid;

			std::shared_ptr<GLInterface> gl;

			GLenum type_i;
			GLuint id_i;

			Shader() = delete;
			Shader(const Shader& old) = delete;
			Shader(Shader&& old) = delete;
			Shader& operator=(const Shader& old) = delete;
			Shader& operator=(Shader&& old) = delete;

			void Delete();

		public:
			using CompileFlags = std::set<std::string>;

		protected:
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

		public:
			virtual ~Shader();

			///@brief OpenGl shader id getter
			virtual GLuint id()const{return id_i;};

			///@brief Shader type getter
			virtual GLenum type()const{return type_i;};

			///@brief Returns code that was passed to OpenGL.
			std::string code()const{return code_i;}
			operator bool(){return isValid;}
	};

	class ShaderFromFile : public Shader{
		friend class ObjectFactory;

		private:
			std::string readFile(std::string path);

		protected:
			/**
			@brief Shader factory taking file path.
			@param shaderType - Type of shader to create.
			@param filePath - Path to file containing shader code.
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
			ShaderFromFile(const GLenum shaderType,
							const std::string filePath,
							const CompileFlags& compileFlags = {},
							std::shared_ptr<GLInterface> interface = std::make_shared<GL>()
							):Shader(shaderType,
									readFile(filePath),
									compileFlags,
									interface){};
	};

}

#endif // INCLUDE_OGL_SHADER_HPP_
