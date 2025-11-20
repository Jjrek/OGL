#include "variable.hpp"
#include "log.hpp"

namespace ogl{

	Variable::Variable(Params params, std::shared_ptr<GLInterface> interface)noexcept{
		gl = interface;
		Variable::params = params;
	}


	Uniform::Uniform(Params params, std::shared_ptr<GLInterface> interface)noexcept:
		Variable(params, interface){
	}

	void Uniform::pass(void* pDataptr){
		GLuint& address = params.address;
		GLint& variableType = params.variableType;
		GLuint& programId = params.programId;
		switch(variableType){
			case  GL_SAMPLER_1D 									: gl->glProgramUniform1iv(programId, address, 1, static_cast<GLint*>( pDataptr)); break;
			case  GL_SAMPLER_1D_SHADOW								: gl->glProgramUniform1iv(programId, address, 1, static_cast<GLint*>( pDataptr)); break;
			case  GL_SAMPLER_1D_ARRAY								: gl->glProgramUniform1iv(programId, address, 1, static_cast<GLint*>( pDataptr)); break;
			case  GL_SAMPLER_1D_ARRAY_SHADOW						: gl->glProgramUniform1iv(programId, address, 1, static_cast<GLint*>( pDataptr)); break;
			case  GL_SAMPLER_2D										: gl->glProgramUniform1iv(programId, address, 1, static_cast<GLint*>( pDataptr)); break;
			case  GL_SAMPLER_2D_SHADOW								: gl->glProgramUniform1iv(programId, address, 1, static_cast<GLint*>( pDataptr)); break;
			case  GL_SAMPLER_2D_ARRAY								: gl->glProgramUniform1iv(programId, address, 1, static_cast<GLint*>( pDataptr)); break;
			case  GL_SAMPLER_2D_ARRAY_SHADOW						: gl->glProgramUniform1iv(programId, address, 1, static_cast<GLint*>( pDataptr)); break;
			case  GL_SAMPLER_3D										: gl->glProgramUniform1iv(programId, address, 1, static_cast<GLint*>( pDataptr)); break;
			case  GL_SAMPLER_CUBE									: gl->glProgramUniform1iv(programId, address, 1, static_cast<GLint*>( pDataptr)); break;
			case  GL_SAMPLER_CUBE_SHADOW							: gl->glProgramUniform1iv(programId, address, 1, static_cast<GLint*>( pDataptr)); break;
			case  GL_SAMPLER_CUBE_MAP_ARRAY 						: gl->glProgramUniform1iv(programId, address, 1, static_cast<GLint*>( pDataptr)); break;
			case  GL_SAMPLER_CUBE_MAP_ARRAY_SHADOW 					: gl->glProgramUniform1iv(programId, address, 1, static_cast<GLint*>( pDataptr)); break;
			case  GL_INT				                            : gl->glProgramUniform1iv(programId, address, 1, static_cast<GLint*>( pDataptr)); break;
			case  GL_INT_VEC2 			                            : gl->glProgramUniform2iv(programId, address, 1, static_cast<GLint*>( pDataptr)); break;
			case  GL_INT_VEC3 			                            : gl->glProgramUniform3iv(programId, address, 1, static_cast<GLint*>( pDataptr)); break;
			case  GL_INT_VEC4 			                            : gl->glProgramUniform4iv(programId, address, 1, static_cast<GLint*>( pDataptr)); break;
			case  GL_UNSIGNED_INT		                            : gl->glProgramUniform1uiv(programId, address, 1, static_cast<GLuint*>( pDataptr)); break;
			case  GL_UNSIGNED_INT_VEC2	                            : gl->glProgramUniform2uiv(programId, address, 1, static_cast<GLuint*>( pDataptr)); break;
			case  GL_UNSIGNED_INT_VEC3                              : gl->glProgramUniform3uiv(programId, address, 1, static_cast<GLuint*>( pDataptr)); break;
			case  GL_UNSIGNED_INT_VEC4                              : gl->glProgramUniform4uiv(programId, address, 1, static_cast<GLuint*>( pDataptr)); break;
			case  GL_FLOAT			                                : gl->glProgramUniform1fv(programId, address, 1, static_cast<GLfloat*>( pDataptr)); break;
			case  GL_FLOAT_VEC2 	                                : gl->glProgramUniform2fv(programId, address, 1, static_cast<GLfloat*>( pDataptr)); break;
			case  GL_FLOAT_VEC3 	                                : gl->glProgramUniform3fv(programId, address, 1, static_cast<GLfloat*>( pDataptr)); break;
			case  GL_FLOAT_VEC4 	                                : gl->glProgramUniform4fv(programId, address, 1, static_cast<GLfloat*>( pDataptr)); break;
			case  GL_FLOAT_MAT2 	                                : gl->glProgramUniformMatrix2fv(programId, address, 1, static_cast<GLfloat*>( pDataptr)); break;
			case  GL_FLOAT_MAT2x3 	                                : gl->glProgramUniformMatrix2x3fv(programId, address, 1, static_cast<GLfloat*>( pDataptr)); break;
			case  GL_FLOAT_MAT2x4 	                                : gl->glProgramUniformMatrix2x4fv(programId, address, 1, static_cast<GLfloat*>( pDataptr)); break;
			case  GL_FLOAT_MAT3x2 	                                : gl->glProgramUniformMatrix3x2fv(programId, address, 1, static_cast<GLfloat*>( pDataptr)); break;
			case  GL_FLOAT_MAT3 	                                : gl->glProgramUniformMatrix3fv(programId, address, 1, static_cast<GLfloat*>( pDataptr)); break;
			case  GL_FLOAT_MAT3x4 	                                : gl->glProgramUniformMatrix3x4fv(programId, address, 1, static_cast<GLfloat*>( pDataptr)); break;
			case  GL_FLOAT_MAT4x2 	                                : gl->glProgramUniformMatrix4x2fv(programId, address, 1, static_cast<GLfloat*>( pDataptr)); break;
			case  GL_FLOAT_MAT4x3 	                                : gl->glProgramUniformMatrix4x3fv(programId, address, 1, static_cast<GLfloat*>( pDataptr)); break;
			case  GL_FLOAT_MAT4 	                                : gl->glProgramUniformMatrix4fv(programId, address, 1, static_cast<GLfloat*>( pDataptr)); break;
			default              	                                : break;
		}
	}


	Buffered::Buffered(Params params, std::shared_ptr<GLInterface> interface)noexcept:
		Variable(params, interface){
	}


	Attribute::Attribute(Params params, std::shared_ptr<GLInterface> interface)noexcept:
		Buffered(params, interface){
	}

	void Attribute::attachBuffer(std::shared_ptr<DataBuffer> buffer){
		GLuint& address = params.address;
		GLint& variableType = params.variableType;
		gl->glBindBuffer(GL_ARRAY_BUFFER, buffer->id());
		switch(variableType){
			case	GL_BOOL						 	:   gl->glVertexAttribPointer(address, 1, GL_BOOL, GL_FALSE, 0, 0); break;
			case	GL_BYTE						 	:   gl->glVertexAttribIPointer(address, 1, GL_BYTE, 0, 0); break;
			case	GL_INT_2_10_10_10_REV		   	:   gl->glVertexAttribIPointer(address, 1, GL_INT_2_10_10_10_REV, 0, 0); break;
			case	GL_SHORT						:   gl->glVertexAttribIPointer(address, 1, GL_SHORT, 0, 0); break;
			case	GL_INT						  	:   gl->glVertexAttribIPointer(address, 1, GL_INT, 0, 0); break;
			case	GL_INT_VEC2					 	:   gl->glVertexAttribIPointer(address, 2, GL_INT, 0, 0); break;
			case	GL_INT_VEC3					 	:   gl->glVertexAttribIPointer(address, 3, GL_INT, 0, 0); break;
			case	GL_INT_VEC4					 	:   gl->glVertexAttribIPointer(address, 4, GL_INT, 0, 0); break;
			case	GL_UNSIGNED_INT					:   gl->glVertexAttribIPointer(address, 1, GL_UNSIGNED_INT, 0, 0); break;
			case	GL_UNSIGNED_INT_VEC2			:   gl->glVertexAttribIPointer(address, 2, GL_UNSIGNED_INT, 0, 0); break;
			case	GL_UNSIGNED_INT_VEC3			:   gl->glVertexAttribIPointer(address, 3, GL_UNSIGNED_INT, 0, 0); break;
			case	GL_UNSIGNED_INT_VEC4			:   gl->glVertexAttribIPointer(address, 4, GL_UNSIGNED_INT, 0, 0); break;
			case	GL_UNSIGNED_INT_2_10_10_10_REV  :   gl->glVertexAttribIPointer(address, 1, GL_UNSIGNED_INT_2_10_10_10_REV, 0, 0); break;
			case	GL_UNSIGNED_INT_10F_11F_11F_REV	:   gl->glVertexAttribIPointer(address, 1, GL_UNSIGNED_INT_10F_11F_11F_REV, 0, 0); break;
			case	GL_HALF_FLOAT				   	:   gl->glVertexAttribPointer(address, 1, GL_HALF_FLOAT, GL_FALSE, 0, 0); break;
			case	GL_FLOAT						:   gl->glVertexAttribPointer(address, 1, GL_FLOAT, GL_FALSE, 0, 0); break;
			case	GL_FLOAT_VEC2				   	:  	gl->glVertexAttribPointer(address, 2, GL_FLOAT, GL_FALSE, 0, 0); break;
			case	GL_FLOAT_VEC3				   	:   gl->glVertexAttribPointer(address, 3, GL_FLOAT, GL_FALSE, 0, 0); break;
			case	GL_FLOAT_VEC4				   	:   gl->glVertexAttribPointer(address, 4, GL_FLOAT, GL_FALSE, 0, 0); break;
			case	GL_DOUBLE					   	:   gl->glVertexAttribPointer(address, 1, GL_DOUBLE, GL_FALSE, 0, 0); break;
			case	GL_DOUBLE_VEC2				  	:   gl->glVertexAttribPointer(address, 2, GL_DOUBLE, GL_FALSE, 0, 0); break;
			case	GL_DOUBLE_VEC3				  	:   gl->glVertexAttribPointer(address, 3, GL_DOUBLE, GL_FALSE, 0, 0); break;
			case	GL_DOUBLE_VEC4				  	:   gl->glVertexAttribPointer(address, 4, GL_DOUBLE, GL_FALSE, 0, 0); break;

			case	GL_FLOAT_MAT4				   	:  	gl->glVertexAttribPointer(address+3, 4, GL_FLOAT, GL_FALSE, 16*sizeof(float), (void*)(12*sizeof(float)));
														gl->glVertexAttribPointer(address+2, 4, GL_FLOAT, GL_FALSE, 16*sizeof(float), (void*)(8*sizeof(float)));
														gl->glVertexAttribPointer(address+1, 4, GL_FLOAT, GL_FALSE, 16*sizeof(float), (void*)(4*sizeof(float)));
														gl->glVertexAttribPointer(address,   4, GL_FLOAT, GL_FALSE, 16*sizeof(float), (void*)(0));  break;

			case	GL_FLOAT_MAT3					:	gl->glVertexAttribPointer(address+2, 3, GL_FLOAT, GL_FALSE, 9*sizeof(float), (void*)(6*sizeof(float)));
														gl->glVertexAttribPointer(address+1, 3, GL_FLOAT, GL_FALSE, 9*sizeof(float), (void*)(3*sizeof(float)));
														gl->glVertexAttribPointer(address,   3, GL_FLOAT, GL_FALSE, 9*sizeof(float), (void*)(0));  break;

			case	GL_FLOAT_MAT2					:	gl->glVertexAttribPointer(address+1, 2, GL_FLOAT, GL_FALSE, 4*sizeof(float), (void*)(2*sizeof(float)));
														gl->glVertexAttribPointer(address,   2, GL_FLOAT, GL_FALSE, 4*sizeof(float), (void*)(0));  break;
			default              	               	: 	break;
		}
	}

	void Attribute::MakeAtributeInstanced(int divisor){
		GLuint& address = params.address;
		GLint& variableType = params.variableType;
		switch (variableType){
			case GL_FLOAT_MAT4	:	gl->glVertexAttribDivisor(address+3, divisor); [[fallthrough]];
			case GL_FLOAT_MAT3	:	gl->glVertexAttribDivisor(address+2, divisor); [[fallthrough]];
			case GL_FLOAT_MAT2	:	gl->glVertexAttribDivisor(address+1, divisor); [[fallthrough]];
			default				:	gl->glVertexAttribDivisor(address, divisor); break;
		}
	}


	Buffer_Block::Buffer_Block(Params params, std::shared_ptr<GLInterface> interface)noexcept:
		Buffered(params, interface){
	}

	void Buffer_Block::attachBuffer(std::shared_ptr<DataBuffer> buffer){
		GLuint& address = params.address;
		GLint& variableType = params.variableType;
		GLuint& programId = params.programId;
		switch(variableType){
			case GL_UNIFORM_BLOCK :
					gl->glUniformBlockBinding(programId, address, buffer->bindingPoint());
					break;
			case GL_SHADER_STORAGE_BLOCK :
					gl->glShaderStorageBlockBinding(programId, address, buffer->bindingPoint());
					break;
		}
	}
}

