#include "GLInterface.hpp"

#include <GL/glew.h>
#include <GL/gl.h>

/// @cond IGNORE_IN_DOCUMENTATION

#define link1(name,t1,v1) \
	void GL::name(t1 v1){::name(v1);}
#define link2(name,t1,v1,t2,v2) \
	void GL::name(t1 v1,t2 v2){::name(v1,v2);}
#define link3(name,t1,v1,t2,v2,t3,v3) \
	void GL::name(t1 v1,t2 v2,t3 v3){::name(v1,v2,v3);}
#define link4(name,t1,v1,t2,v2,t3,v3,t4,v4) \
	void GL::name(t1 v1,t2 v2,t3 v3,t4 v4){::name(v1,v2,v3,v4);}
#define linkMat4(name,t1,v1,t2,v2,t3,v3,t4,v4) \
	void GL::name(t1 v1, t2 v2,t3 v3,t4 v4){::name(v1,v2,v3,GL_FALSE,v4);}
#define link5(name,t1,v1,t2,v2,t3,v3,t4,v4,t5,v5) \
	void GL::name(t1 v1,t2 v2,t3 v3,t4 v4,t5 v5){::name(v1,v2,v3,v4,v5);}
#define link6(name,t1,v1,t2,v2,t3,v3,t4,v4,t5,v5,t6,v6) \
	void GL::name(t1 v1,t2 v2,t3 v3,t4 v4,t5 v5, t6 v6){::name(v1,v2,v3,v4,v5,v6);}


namespace ogl {
	//Shader functions
	GLuint GL::glCreateShader(GLenum type){
		return ::glCreateShader(type);
	}
	void GL::glShaderSource(GLuint id, const GLchar* const code){
		::glShaderSource(id,1,&code,nullptr);
	}
	link1(glCompileShader,GLuint,id)
	link3(glGetShaderiv,GLuint,id,GLenum,pname,GLint*,param)
	link4(glGetShaderInfoLog,GLuint,id,GLsizei,bufSize,GLsizei*,length,GLchar*,infoLog)
	link4(glGetShaderSource,GLuint,id,GLsizei,maxLength,GLsizei*,length,GLchar*,source)
	link1(glDeleteShader,GLuint,id)

	//Buffer functions
	link2(glCreateBuffers,GLsizei,n,GLuint*,buffer)
	link2(glDeleteBuffers,GLsizei,n,GLuint*,buffer)
	link4(glNamedBufferData,GLuint,buffer,GLsizeiptr,size,const void*,data,GLenum,usage)
	link4(glNamedBufferSubData,GLuint,buffer,GLintptr,offset,GLsizeiptr,size,const void*,data)

	//Program functions
	GLuint GL::glCreateProgram(){
		return ::glCreateProgram();
	}
	link2(glAttachShader,GLuint,id,GLuint,shader)
	link1(glLinkProgram,GLuint,id)
	link2(glDetachShader,GLuint,id,GLuint,shader)
	link3(glGetProgramiv,GLuint,id,GLenum,pname,GLint*,param)
	link4(glGetProgramInfoLog,GLuint,id,GLsizei,bufSize,GLsizei*,length,GLchar*,infoLog)
	link1(glUseProgram,GLuint,id)
	link2(glGenVertexArrays,GLsizei,n,GLuint*,arrays)
	link1(glBindVertexArray,GLuint,array)
	link1(glDeleteProgram,GLuint,id)
	link2(glDeleteVertexArrays,GLsizei,n,GLuint*,arrays)
	//Program introspection
	link4(glGetProgramInterfaceiv,GLuint,program,GLenum,programInterface,GLenum,pname,GLint*,params)
	link6(glGetProgramResourceName,GLuint,program,GLenum,programInterface,GLuint,index,GLsizei,bufSize,GLsizei*,length,GLchar*,name)
	void GL::glGetProgramResourceiv(GLuint program, GLenum programInterface, GLuint index, GLsizei propCount, const GLenum* props, GLsizei bufSize, GLsizei *length, GLint *params){
		::glGetProgramResourceiv(program,programInterface,index,propCount,props,bufSize,length,params);
	}
	GLuint GL::glGetUniformBlockIndex(GLuint program, const GLchar* uniformBlockName){
		return ::glGetUniformBlockIndex(program,uniformBlockName);
	}
	GLuint GL::glGetProgramResourceIndex(GLuint program, GLenum programInterface, const GLchar* name){
		return ::glGetProgramResourceIndex(program,programInterface,name);
	}

	//Variable functions
	link4(glProgramUniform1iv,			GLuint,program,GLint,location,GLsizei,count,const GLint*,value)
	link4(glProgramUniform2iv,			GLuint,program,GLint,location,GLsizei,count,const GLint*,value)
	link4(glProgramUniform3iv,			GLuint,program,GLint,location,GLsizei,count,const GLint*,value)
	link4(glProgramUniform4iv,			GLuint,program,GLint,location,GLsizei,count,const GLint*,value)
	link4(glProgramUniform1uiv,			GLuint,program,GLint,location,GLsizei,count,const GLuint*,value)
	link4(glProgramUniform2uiv,			GLuint,program,GLint,location,GLsizei,count,const GLuint*,value)
	link4(glProgramUniform3uiv,			GLuint,program,GLint,location,GLsizei,count,const GLuint*,value)
	link4(glProgramUniform4uiv,			GLuint,program,GLint,location,GLsizei,count,const GLuint*,value)
	link4(glProgramUniform1fv,			GLuint,program,GLint,location,GLsizei,count,const GLfloat*,value)
	link4(glProgramUniform2fv,			GLuint,program,GLint,location,GLsizei,count,const GLfloat*,value)
	link4(glProgramUniform3fv,			GLuint,program,GLint,location,GLsizei,count,const GLfloat*,value)
	link4(glProgramUniform4fv,			GLuint,program,GLint,location,GLsizei,count,const GLfloat*,value)
	linkMat4(glProgramUniformMatrix2fv,	GLuint,program,GLint,location,GLsizei,count,const GLfloat*,value)
	linkMat4(glProgramUniformMatrix2x3fv,	GLuint,program,GLint,location,GLsizei,count,const GLfloat*,value)
	linkMat4(glProgramUniformMatrix2x4fv,	GLuint,program,GLint,location,GLsizei,count,const GLfloat*,value)
	linkMat4(glProgramUniformMatrix3x2fv,	GLuint,program,GLint,location,GLsizei,count,const GLfloat*,value)
	linkMat4(glProgramUniformMatrix3fv,	GLuint,program,GLint,location,GLsizei,count,const GLfloat*,value)
	linkMat4(glProgramUniformMatrix3x4fv,	GLuint,program,GLint,location,GLsizei,count,const GLfloat*,value)
	linkMat4(glProgramUniformMatrix4x2fv,	GLuint,program,GLint,location,GLsizei,count,const GLfloat*,value)
	linkMat4(glProgramUniformMatrix4x3fv,	GLuint,program,GLint,location,GLsizei,count,const GLfloat*,value)
	linkMat4(glProgramUniformMatrix4fv,	GLuint,program,GLint,location,GLsizei,count,const GLfloat*,value)
	link2(glBindBuffer,GLenum,target,GLuint,buffer)
	link6(glVertexAttribPointer,GLuint,index,GLint,size,GLenum,type,GLboolean,normalized,GLsizei,stride,const void*,pointer)
	link5(glVertexAttribIPointer,GLuint,index,GLint,size,GLenum,type,GLsizei,stride,const void*,pointer)
	link2(glVertexAttribDivisor,GLuint,index,GLuint,divisor)
	link3(glUniformBlockBinding,GLuint,program,GLuint,uniformBlockIndex,GLuint,uniformBlockBinding)
	link3(glShaderStorageBlockBinding,GLuint,program,GLuint,storageBlockIndex,GLuint,storageBlockBinding)
}

/// @endcond IGNORE_IN_DOCUMENTATION

