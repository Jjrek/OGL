#include "GLInterface.hpp"

#include <GL/glew.h>
#include <GL/gl.h>

namespace ogl {

	GLuint GL::glCreateShader(GLenum type){
		return ::glCreateShader(type);
	}

	void GL::glShaderSource(GLuint id, const GLchar* const code){
		::glShaderSource(id,1,&code,nullptr);
	}

	void GL::glCompileShader(GLuint id){
		::glCompileShader(id);
	}

	void GL::glGetShaderiv(GLuint id, GLenum pname, GLint* param){
		::glGetShaderiv(id, pname, param);
	}

	void GL::glGetShaderInfoLog(GLuint id, GLsizei bufSize, GLsizei* length, GLchar* infoLog){
		::glGetShaderInfoLog(id, bufSize, length, infoLog);
	}

	void GL::glGetShaderSource(GLuint id, GLsizei maxLength, GLsizei* length, GLchar* source){
		::glGetShaderSource(id, maxLength, length, source);
	}

	void GL::glDeleteShader(GLuint id){
		::glDeleteShader(id);
	}

}
