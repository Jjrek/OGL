#ifndef INCLUDE_GL_MOCK_HPP_
#define INCLUDE_GL_MOCK_HPP_

#include <gmock/gmock.h>

#include "GLInterface.hpp"

class GLMock: public ogl::GLInterface{
	public:
		MOCK_METHOD(GLuint, glCreateShader, (GLenum type), (override));
		MOCK_METHOD(void, glShaderSource, (GLuint id, const GLchar* const code), (override));
		MOCK_METHOD(void, glCompileShader, (GLuint id), (override));
		MOCK_METHOD(void, glGetShaderiv, (GLuint id, GLenum pname, GLint* param), (override));
		MOCK_METHOD(void, glGetShaderInfoLog, (GLuint id, GLsizei bufSize, GLsizei* length, GLchar* infoLog), (override));
		MOCK_METHOD(void, glGetShaderSource, (GLuint id, GLsizei maxLength, GLsizei* length, GLchar* source), (override));
		MOCK_METHOD(void, glDeleteShader, (GLuint id), (override));

		MOCK_METHOD(GLuint, glCreateProgram, (), (override));
		MOCK_METHOD(void, glAttachShader, (GLuint id, GLuint shader), (override));
		MOCK_METHOD(void, glLinkProgram, (GLuint id), (override));
		MOCK_METHOD(void, glDetachShader, (GLuint id, GLuint shader), (override));
		MOCK_METHOD(void, glGetProgramiv, (GLuint id, GLenum pname, GLint* param), (override));
		MOCK_METHOD(void, glGetProgramInfoLog, (GLuint id, GLsizei bufSize, GLsizei* length, GLchar* infoLog), (override));
		MOCK_METHOD(void, glUseProgram, (GLuint id), (override));
		MOCK_METHOD(void, glGenVertexArrays, (GLsizei n, GLuint* arrays), (override));
		MOCK_METHOD(void, glBindVertexArray, (GLuint array), (override));
		MOCK_METHOD(void, glDeleteProgram, (GLuint id), (override));
};


#endif // INCLUDE_GL_MOCK_HPP_
