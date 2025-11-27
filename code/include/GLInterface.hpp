#ifndef INCLUDE_OGL_GLINTERFACE_HPP_
#define INCLUDE_OGL_GLINTERFACE_HPP_

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

			//Buffer functions
			virtual void glCreateBuffers(GLsizei n, GLuint* buffer) = 0;
			virtual void glDeleteBuffers(GLsizei n, GLuint* buffer) = 0;
			virtual void glBindBufferBase(GLenum target, GLuint index, GLuint buffer) = 0;
			virtual void glNamedBufferData(GLuint buffer, GLsizeiptr size, const void *data, GLenum usage) = 0;
			virtual void glNamedBufferSubData(GLuint buffer, GLintptr offset, GLsizeiptr size, const void *data) = 0;

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
			virtual void glDeleteVertexArrays(GLsizei n, GLuint* arrays) = 0;
			//Program introspection
			virtual void glGetProgramInterfaceiv(GLuint program, GLenum programInterface, GLenum pname, GLint* params) = 0;
			virtual void glGetProgramResourceiv(GLuint program, GLenum programInterface, GLuint index, GLsizei propCount, const GLenum* props, GLsizei bufSize, GLsizei *length, GLint *params) = 0;
			virtual void glGetProgramResourceName(GLuint program, GLenum programInterface, GLuint index, GLsizei bufSize, GLsizei* length, GLchar *name) = 0;
			virtual GLuint glGetUniformBlockIndex(GLuint program, const GLchar* uniformBlockName) = 0;
			virtual GLuint glGetProgramResourceIndex(GLuint program, GLenum programInterface, const GLchar* name) = 0;

			//Variable functions
			virtual void glProgramUniform1iv		(GLuint program, GLint location, GLsizei count, const GLint* value) = 0;
			virtual void glProgramUniform2iv		(GLuint program, GLint location, GLsizei count, const GLint* value) = 0;
			virtual void glProgramUniform3iv		(GLuint program, GLint location, GLsizei count, const GLint* value) = 0;
			virtual void glProgramUniform4iv		(GLuint program, GLint location, GLsizei count, const GLint* value) = 0;
			virtual void glProgramUniform1uiv		(GLuint program, GLint location, GLsizei count, const GLuint* value) = 0;
			virtual void glProgramUniform2uiv		(GLuint program, GLint location, GLsizei count, const GLuint* value) = 0;
			virtual void glProgramUniform3uiv		(GLuint program, GLint location, GLsizei count, const GLuint* value) = 0;
			virtual void glProgramUniform4uiv		(GLuint program, GLint location, GLsizei count, const GLuint* value) = 0;
			virtual void glProgramUniform1fv		(GLuint program, GLint location, GLsizei count, const GLfloat* value) = 0;
			virtual void glProgramUniform2fv		(GLuint program, GLint location, GLsizei count, const GLfloat* value) = 0;
			virtual void glProgramUniform3fv		(GLuint program, GLint location, GLsizei count, const GLfloat* value) = 0;
			virtual void glProgramUniform4fv		(GLuint program, GLint location, GLsizei count, const GLfloat* value) = 0;
			virtual void glProgramUniformMatrix2fv	(GLuint program, GLint location, GLsizei count, const GLfloat* value) = 0;
			virtual void glProgramUniformMatrix2x3fv(GLuint program, GLint location, GLsizei count, const GLfloat* value) = 0;
			virtual void glProgramUniformMatrix2x4fv(GLuint program, GLint location, GLsizei count, const GLfloat* value) = 0;
			virtual void glProgramUniformMatrix3x2fv(GLuint program, GLint location, GLsizei count, const GLfloat* value) = 0;
			virtual void glProgramUniformMatrix3fv	(GLuint program, GLint location, GLsizei count, const GLfloat* value) = 0;
			virtual void glProgramUniformMatrix3x4fv(GLuint program, GLint location, GLsizei count, const GLfloat* value) = 0;
			virtual void glProgramUniformMatrix4x2fv(GLuint program, GLint location, GLsizei count, const GLfloat* value) = 0;
			virtual void glProgramUniformMatrix4x3fv(GLuint program, GLint location, GLsizei count, const GLfloat* value) = 0;
			virtual void glProgramUniformMatrix4fv	(GLuint program, GLint location, GLsizei count, const GLfloat* value) = 0;
			virtual void glBindBuffer(GLenum target, GLuint buffer) = 0;
			virtual void glEnableVertexAttribArray(GLuint index) = 0;
			virtual void glVertexAttribPointer(GLuint index, GLint size, GLenum type, GLboolean normalized, GLsizei stride, const void* pointer) = 0;
			virtual void glVertexAttribIPointer(GLuint index, GLint size, GLenum type, GLsizei stride, const void* pointer) = 0;
			virtual void glVertexAttribDivisor(GLuint index, GLuint divisor) = 0;
			virtual void glUniformBlockBinding(GLuint program, GLuint uniformBlockIndex, GLuint uniformBlockBinding) = 0;
			virtual void glShaderStorageBlockBinding(GLuint program, GLuint storageBlockIndex, GLuint storageBlockBinding) = 0;
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

			//Buffer functions
			void glCreateBuffers(GLsizei n, GLuint* buffer)final;
			void glDeleteBuffers(GLsizei n, GLuint* buffer)final;
			void glBindBufferBase(GLenum target, GLuint index, GLuint buffer)final;
			void glNamedBufferData(GLuint buffer, GLsizeiptr size, const void *data, GLenum usage)final;
			void glNamedBufferSubData(GLuint buffer, GLintptr offset, GLsizeiptr size, const void *data)final;

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
			void glDeleteVertexArrays(GLsizei n, GLuint* arrays)final;
			//Program introspection
			void glGetProgramInterfaceiv(GLuint program, GLenum programInterface, GLenum pname, GLint* params)final;
			void glGetProgramResourceiv(GLuint program, GLenum programInterface, GLuint index, GLsizei propCount, const GLenum* props, GLsizei bufSize, GLsizei *length, GLint *params)final;
			void glGetProgramResourceName(GLuint program, GLenum programInterface, GLuint index, GLsizei bufSize, GLsizei* length, GLchar *name)final;
			GLuint glGetUniformBlockIndex(GLuint program, const GLchar* uniformBlockName)final;
			GLuint glGetProgramResourceIndex(GLuint program, GLenum programInterface, const GLchar* name)final;

			//Variable functions
			void glProgramUniform1iv		(GLuint program, GLint location, GLsizei count, const GLint* value)final;
			void glProgramUniform2iv		(GLuint program, GLint location, GLsizei count, const GLint* value)final;
			void glProgramUniform3iv		(GLuint program, GLint location, GLsizei count, const GLint* value)final;
			void glProgramUniform4iv		(GLuint program, GLint location, GLsizei count, const GLint* value)final;
			void glProgramUniform1uiv		(GLuint program, GLint location, GLsizei count, const GLuint* value)final;
			void glProgramUniform2uiv		(GLuint program, GLint location, GLsizei count, const GLuint* value)final;
			void glProgramUniform3uiv		(GLuint program, GLint location, GLsizei count, const GLuint* value)final;
			void glProgramUniform4uiv		(GLuint program, GLint location, GLsizei count, const GLuint* value)final;
			void glProgramUniform1fv		(GLuint program, GLint location, GLsizei count, const GLfloat* value)final;
			void glProgramUniform2fv		(GLuint program, GLint location, GLsizei count, const GLfloat* value)final;
			void glProgramUniform3fv		(GLuint program, GLint location, GLsizei count, const GLfloat* value)final;
			void glProgramUniform4fv		(GLuint program, GLint location, GLsizei count, const GLfloat* value)final;
			void glProgramUniformMatrix2fv	(GLuint program, GLint location, GLsizei count, const GLfloat* value)final;
			void glProgramUniformMatrix2x3fv(GLuint program, GLint location, GLsizei count, const GLfloat* value)final;
			void glProgramUniformMatrix2x4fv(GLuint program, GLint location, GLsizei count, const GLfloat* value)final;
			void glProgramUniformMatrix3x2fv(GLuint program, GLint location, GLsizei count, const GLfloat* value)final;
			void glProgramUniformMatrix3fv	(GLuint program, GLint location, GLsizei count, const GLfloat* value)final;
			void glProgramUniformMatrix3x4fv(GLuint program, GLint location, GLsizei count, const GLfloat* value)final;
			void glProgramUniformMatrix4x2fv(GLuint program, GLint location, GLsizei count, const GLfloat* value)final;
			void glProgramUniformMatrix4x3fv(GLuint program, GLint location, GLsizei count, const GLfloat* value)final;
			void glProgramUniformMatrix4fv	(GLuint program, GLint location, GLsizei count, const GLfloat* value)final;
			void glBindBuffer(GLenum target, GLuint buffer)final;
			void glEnableVertexAttribArray(GLuint index)final;
			void glVertexAttribPointer(GLuint index, GLint size, GLenum type, GLboolean normalized, GLsizei stride, const void* pointer)final;
			void glVertexAttribIPointer(GLuint index, GLint size, GLenum type, GLsizei stride, const void* pointer)final;
			void glVertexAttribDivisor(GLuint index, GLuint divisor)final;
			void glUniformBlockBinding(GLuint program, GLuint uniformBlockIndex, GLuint uniformBlockBinding)final;
			void glShaderStorageBlockBinding(GLuint program, GLuint storageBlockIndex, GLuint storageBlockBinding)final;
	};

}
#endif // INCLUDE_OGL_GLINTERFACE_HPP_
