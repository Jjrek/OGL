#ifndef INCLUDE_GLINTERFACE_HPP_
#define INCLUDE_GLINTERFACE_HPP_

#include <GL/glew.h>
#include <GL/gl.h>

namespace ogl {

	///@brief Abstract OpenGL interface
	class GLInterface{
		public:
			virtual ~GLInterface(){};

			//Shader functions
			virtual GLuint glCreateShader(GLenum type) = 0;
			virtual void glShaderSource(GLuint id, const GLchar* const code) = 0;
			virtual void glCompileShader(GLuint id) = 0;
			virtual void glGetShaderiv(GLuint id, GLenum pname, GLint* param) = 0;
			virtual void glGetShaderInfoLog(GLuint id, GLsizei bufSize, GLsizei* length, GLchar* infoLog) = 0;
			virtual void glGetShaderSource(GLuint id, GLsizei maxLength, GLsizei* length, GLchar* source) = 0;
			virtual void glDeleteShader(GLuint id) = 0;

			//Program functions
			virtual GLuint glCreateProgram() = 0;
			virtual void glAttachShader(GLuint id, GLuint shader) = 0;
			virtual void glLinkProgram(GLuint id) = 0;
			virtual void glDetachShader(GLuint id, GLuint shader) = 0;
			virtual void glGetProgramiv(GLuint id, GLenum pname, GLint* param) = 0;
			virtual void glGetProgramInfoLog(GLuint id, GLsizei bufSize, GLsizei* length, GLchar* infoLog) = 0;
			virtual void glUseProgram(GLuint id) = 0;
			virtual void glGenVertexArrays(GLsizei n, GLuint* arrays) = 0;
			virtual void glBindVertexArray(GLuint array) = 0;
			virtual void glDeleteProgram(GLuint id) = 0;
	};

	///@brief OpenGL interface implementation
	class GL : public GLInterface{
		public:
			~GL(){};

			//Shader functions
			GLuint glCreateShader(GLenum type)final;
			void glShaderSource(GLuint id, const GLchar* const code)final;
			void glCompileShader(GLuint id)final;
			void glGetShaderiv(GLuint id, GLenum pname, GLint* param)final;
			void glGetShaderInfoLog(GLuint id, GLsizei bufSize, GLsizei* length, GLchar* infoLog)final;
			void glGetShaderSource(GLuint id, GLsizei maxLength, GLsizei* length, GLchar* source)final;
			void glDeleteShader(GLuint id)final;

			//Program functions
			GLuint glCreateProgram()final;
			void glAttachShader(GLuint id, GLuint shader)final;
			void glLinkProgram(GLuint id)final;
			void glDetachShader(GLuint id, GLuint shader)final;
			void glGetProgramiv(GLuint id, GLenum pname, GLint* param)final;
			void glGetProgramInfoLog(GLuint id, GLsizei bufSize, GLsizei* length, GLchar* infoLog)final;
			void glUseProgram(GLuint id)final;
			void glGenVertexArrays(GLsizei n, GLuint* arrays)final;
			void glBindVertexArray(GLuint array)final;
			void glDeleteProgram(GLuint id)final;
	};

}
#endif // INCLUDE_GLINTERFACE_HPP_
