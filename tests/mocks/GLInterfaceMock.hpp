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

		MOCK_METHOD(void, glCreateBuffers,(GLsizei n, GLuint* buffer), (override));
		MOCK_METHOD(void, glDeleteBuffers,(GLsizei n, GLuint* buffer), (override));
		MOCK_METHOD(void, glNamedBufferData,(GLuint buffer, GLsizeiptr size, const void *data, GLenum usage), (override));
		MOCK_METHOD(void, glNamedBufferSubData,(GLuint buffer, GLintptr offset, GLsizeiptr size, const void *data), (override));

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
		MOCK_METHOD(void, glDeleteVertexArrays, (GLsizei n, GLuint* arrays), (override));
		MOCK_METHOD(void,glGetProgramInterfaceiv, (GLuint program, GLenum programInterface, GLenum pname, GLint* params), (override));
		MOCK_METHOD(void,glGetProgramResourceiv, (GLuint program, GLenum programInterface, GLuint index, GLsizei propCount, const GLenum* props, GLsizei bufSize, GLsizei *length, GLint *params), (override));
		MOCK_METHOD(void,glGetProgramResourceName, (GLuint program, GLenum programInterface, GLuint index, GLsizei bufSize, GLsizei* length, GLchar *name), (override));
		MOCK_METHOD(GLuint, glGetUniformBlockIndex, (GLuint program, const GLchar* uniformBlockName), (override));
		MOCK_METHOD(GLuint, glGetProgramResourceIndex, (GLuint program, GLenum programInterface, const GLchar* name), (override));

		MOCK_METHOD(void, glProgramUniform1iv,			(GLuint program, GLint location, GLsizei count, const GLint* value), (override));
		MOCK_METHOD(void, glProgramUniform2iv,			(GLuint program, GLint location, GLsizei count, const GLint* value), (override));
		MOCK_METHOD(void, glProgramUniform3iv,			(GLuint program, GLint location, GLsizei count, const GLint* value), (override));
		MOCK_METHOD(void, glProgramUniform4iv,			(GLuint program, GLint location, GLsizei count, const GLint* value), (override));
		MOCK_METHOD(void, glProgramUniform1uiv,			(GLuint program, GLint location, GLsizei count, const GLuint* value), (override));
		MOCK_METHOD(void, glProgramUniform2uiv,			(GLuint program, GLint location, GLsizei count, const GLuint* value), (override));
		MOCK_METHOD(void, glProgramUniform3uiv,			(GLuint program, GLint location, GLsizei count, const GLuint* value), (override));
		MOCK_METHOD(void, glProgramUniform4uiv,			(GLuint program, GLint location, GLsizei count, const GLuint* value), (override));
		MOCK_METHOD(void, glProgramUniform1fv,			(GLuint program, GLint location, GLsizei count, const GLfloat* value), (override));
		MOCK_METHOD(void, glProgramUniform2fv,			(GLuint program, GLint location, GLsizei count, const GLfloat* value), (override));
		MOCK_METHOD(void, glProgramUniform3fv,			(GLuint program, GLint location, GLsizei count, const GLfloat* value), (override));
		MOCK_METHOD(void, glProgramUniform4fv,			(GLuint program, GLint location, GLsizei count, const GLfloat* value), (override));
		MOCK_METHOD(void, glProgramUniformMatrix2fv,	(GLuint program, GLint location, GLsizei count, const GLfloat* value), (override));
		MOCK_METHOD(void, glProgramUniformMatrix2x3fv,	(GLuint program, GLint location, GLsizei count, const GLfloat* value), (override));
		MOCK_METHOD(void, glProgramUniformMatrix2x4fv,	(GLuint program, GLint location, GLsizei count, const GLfloat* value), (override));
		MOCK_METHOD(void, glProgramUniformMatrix3x2fv,	(GLuint program, GLint location, GLsizei count, const GLfloat* value), (override));
		MOCK_METHOD(void, glProgramUniformMatrix3fv,	(GLuint program, GLint location, GLsizei count, const GLfloat* value), (override));
		MOCK_METHOD(void, glProgramUniformMatrix3x4fv,	(GLuint program, GLint location, GLsizei count, const GLfloat* value), (override));
		MOCK_METHOD(void, glProgramUniformMatrix4x2fv,	(GLuint program, GLint location, GLsizei count, const GLfloat* value), (override));
		MOCK_METHOD(void, glProgramUniformMatrix4x3fv,	(GLuint program, GLint location, GLsizei count, const GLfloat* value), (override));
		MOCK_METHOD(void, glProgramUniformMatrix4fv,	(GLuint program, GLint location, GLsizei count, const GLfloat* value), (override));
		MOCK_METHOD(void, glBindBuffer,(GLenum target, GLuint buffer), (override));
		MOCK_METHOD(void, glEnableVertexAttribArray,(GLuint index), (override));
		MOCK_METHOD(void, glVertexAttribPointer, (GLuint index, GLint size, GLenum type, GLboolean normalized, GLsizei stride, const void* pointer), (override));
		MOCK_METHOD(void, glVertexAttribIPointer, (GLuint index, GLint size, GLenum type, GLsizei stride, const void* pointer), (override));
		MOCK_METHOD(void, glVertexAttribDivisor, (GLuint index, GLuint divisor), (override));
		MOCK_METHOD(void, glUniformBlockBinding, (GLuint program, GLuint uniformBlockIndex, GLuint uniformBlockBinding), (override));
		MOCK_METHOD(void, glShaderStorageBlockBinding, (GLuint program, GLuint storageBlockIndex, GLuint storageBlockBinding), (override));
};


#endif // INCLUDE_GL_MOCK_HPP_
