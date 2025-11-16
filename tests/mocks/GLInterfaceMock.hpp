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
};


#endif // INCLUDE_GL_MOCK_HPP_
