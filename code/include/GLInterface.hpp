#ifndef INCLUDE_GLINTERFACE_HPP_
#define INCLUDE_GLINTERFACE_HPP_

#include <GL/glew.h>
#include <GL/gl.h>

namespace ogl {

	///@brief Abstract OpenGL interface
	class GLInterface{
		public:
			virtual ~GLInterface(){};
			virtual GLuint glCreateShader(GLenum type) = 0;
			virtual void glShaderSource(GLuint id, const GLchar* const code) = 0;
			virtual void glCompileShader(GLuint id) = 0;
			virtual void glGetShaderiv(GLuint id, GLenum pname, GLint* param) = 0;
			virtual void glGetShaderInfoLog(GLuint id, GLsizei bufSize, GLsizei* length, GLchar* infoLog) = 0;
			virtual void glGetShaderSource(GLuint id, GLsizei maxLength, GLsizei* length, GLchar* source) = 0;
			virtual void glDeleteShader(GLuint id) = 0;
	};

	///@brief OpenGL interface implementation
	class GL : public GLInterface{
		public:
			~GL(){};
			GLuint glCreateShader(GLenum type)final;
			void glShaderSource(GLuint id, const GLchar* const code)final;
			void glCompileShader(GLuint id)final;
			void glGetShaderiv(GLuint id, GLenum pname, GLint* param)final;
			void glGetShaderInfoLog(GLuint id, GLsizei bufSize, GLsizei* length, GLchar* infoLog)final;
			void glGetShaderSource(GLuint id, GLsizei maxLength, GLsizei* length, GLchar* source)final;
			void glDeleteShader(GLuint id)final;
	};

}
#endif // INCLUDE_GLINTERFACE_HPP_
