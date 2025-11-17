#include "GLInterface.hpp"

#include <GL/glew.h>
#include <GL/gl.h>

namespace ogl {

	//Shader functions
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


	//Program functions
	GLuint GL::glCreateProgram(){
		return ::glCreateProgram();
	}

	void GL::glAttachShader(GLuint id, GLuint shader){
		::glAttachShader(id, shader);
	}

	void GL::glLinkProgram(GLuint id){
		::glLinkProgram(id);
	}

	void GL::glDetachShader(GLuint id, GLuint shader){
		::glDetachShader(id, shader);
	}

	void GL::glGetProgramiv(GLuint id, GLenum pname, GLint* param){
		::glGetProgramiv(id, pname, param);
	}

	void GL::glGetProgramInfoLog(GLuint id, GLsizei bufSize, GLsizei* length, GLchar* infoLog){
		::glGetProgramInfoLog(id, bufSize, length, infoLog);
	}

	void GL::glUseProgram(GLuint id){
		::glUseProgram(id);
	}

	void GL::glGenVertexArrays(GLsizei n, GLuint* arrays){
		::glGenVertexArrays(n, arrays);
	}

	void GL::glBindVertexArray(GLuint array){
		::glBindVertexArray(array);
	}

	void GL::glDeleteProgram(GLuint id){
		::glDeleteProgram(id);
	}

}
