#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include "wrappers/variable.hpp"
#include "log.hpp"

#include "glm/glm.hpp"

#include "GLInterfaceMock.hpp"
#include "dataBufferMock.hpp"

using ::testing::StrictMock;
using ::testing::_;
using ::testing::Return;

using std::any;

GLuint address = 13;
GLuint programId = 37;

GLuint bufferId = 4;
GLuint bufferBindingPoint = 6;

class variable : public testing::Test{
	protected:
		std::shared_ptr<GLMock> gl;
		std::shared_ptr<StrictMock<DataBufferMock>> buffer;

		variable(){
			ogl::Log::Handle().setLoggingFlags(ogl::LogType::NONE);
			gl = std::make_shared<StrictMock<GLMock>>();
			buffer = std::make_shared<StrictMock<DataBufferMock>>();
		}

		void expectBufferBinding(){
			EXPECT_CALL(*buffer, id()).WillOnce(Return(bufferId));
			EXPECT_CALL(*gl, glBindBuffer(GL_ARRAY_BUFFER, bufferId)).Times(1);
		}
};

TEST_F(variable, uniform_int_write){
	ogl::Uniform uniform{{address, GL_INT, programId}, gl};
	int value{17};
	EXPECT_CALL(*gl, glProgramUniform1iv(programId, address, _, _)).WillOnce(
			[=](any,any,any,const int* ptr){EXPECT_EQ(*ptr,value);});
	uniform.pass(&value);
}

TEST_F(variable, uniform_ivec_write){
	ogl::Uniform uniform{{address, GL_INT_VEC3, programId}, gl};
	glm::ivec3 value{1,-7,0};
	EXPECT_CALL(*gl, glProgramUniform3iv(programId, address, _, _)).WillOnce(
			[=](any,any,any,const int* ptr){EXPECT_EQ(*reinterpret_cast<const glm::ivec3*>(ptr),value);});
	uniform.pass(&value);
}

TEST_F(variable, uniform_vec_write){
	ogl::Uniform uniform{{address, GL_FLOAT_VEC2, programId}, gl};
	glm::vec2 value{1.5f,-7.12};
	EXPECT_CALL(*gl, glProgramUniform2fv(programId, address, _, _)).WillOnce(
			[=](any,any,any,const float* ptr){EXPECT_EQ(*reinterpret_cast<const glm::vec2*>(ptr),value);});
	uniform.pass(&value);
}

TEST_F(variable, uniform_mat_write){
	ogl::Uniform uniform{{address, GL_FLOAT_MAT3x2, programId}, gl};
	glm::mat3x2 value{-7.12};
	EXPECT_CALL(*gl, glProgramUniformMatrix3x2fv(programId, address, _, _)).WillOnce(
			[=](any,any,any,const float* ptr){EXPECT_EQ(*reinterpret_cast<const glm::mat3x2*>(ptr),value);});
	uniform.pass(&value);
}

TEST_F(variable, attribute_int_attach_buffer){
	EXPECT_CALL(*gl, glEnableVertexAttribArray(address));
	ogl::Attribute attribute{{address, GL_INT_VEC3, programId}, gl};
	expectBufferBinding();
	EXPECT_CALL(*gl, glVertexAttribIPointer(address,_,_,_,_)).Times(1);
	attribute.attachBuffer(buffer);
}

TEST_F(variable, attribute_non_int_attach_buffer){
	EXPECT_CALL(*gl, glEnableVertexAttribArray(address));
	ogl::Attribute attribute{{address, GL_FLOAT, programId}, gl};
	expectBufferBinding();
	EXPECT_CALL(*gl, glVertexAttribPointer(address,_,_,_,_,_)).Times(1);
	attribute.attachBuffer(buffer);
}

TEST_F(variable, attribute_matrix_attach_buffer){
	EXPECT_CALL(*gl, glEnableVertexAttribArray(address+3));
	EXPECT_CALL(*gl, glEnableVertexAttribArray(address+2));
	EXPECT_CALL(*gl, glEnableVertexAttribArray(address+1));
	EXPECT_CALL(*gl, glEnableVertexAttribArray(address));
	ogl::Attribute attribute{{address, GL_FLOAT_MAT4, programId}, gl};
	expectBufferBinding();
	EXPECT_CALL(*gl, glVertexAttribPointer(address+3,_,_,_,_,_)).Times(1);
	EXPECT_CALL(*gl, glVertexAttribPointer(address+2,_,_,_,_,_)).Times(1);
	EXPECT_CALL(*gl, glVertexAttribPointer(address+1,_,_,_,_,_)).Times(1);
	EXPECT_CALL(*gl, glVertexAttribPointer(address,_,_,_,_,_)).Times(1);
	attribute.attachBuffer(buffer);
}

TEST_F(variable, attribute_instanced_divisor){
	EXPECT_CALL(*gl, glEnableVertexAttribArray(address));
	ogl::Attribute attribute{{address, GL_INT, programId}, gl};
	int divisor = 6;
	EXPECT_CALL(*gl, glVertexAttribDivisor(address,divisor)).Times(1);
	attribute.MakeAtributeInstanced(divisor);
}

TEST_F(variable, attribute_matrix_instanced_divisor){
	EXPECT_CALL(*gl, glEnableVertexAttribArray(address+2));
	EXPECT_CALL(*gl, glEnableVertexAttribArray(address+1));
	EXPECT_CALL(*gl, glEnableVertexAttribArray(address));
	ogl::Attribute attribute{{address, GL_FLOAT_MAT3, programId}, gl};
	int divisor = 6;
	EXPECT_CALL(*gl, glVertexAttribDivisor(address+2,divisor)).Times(1);
	EXPECT_CALL(*gl, glVertexAttribDivisor(address+1,divisor)).Times(1);
	EXPECT_CALL(*gl, glVertexAttribDivisor(address,divisor)).Times(1);
	attribute.MakeAtributeInstanced(divisor);
}

TEST_F(variable, ubo_attach_buffer){
	ogl::Buffer_Block ubo{{address, GL_UNIFORM_BLOCK, programId}, gl};
	EXPECT_CALL(*buffer, bindingPoint()).WillOnce(Return(bufferBindingPoint));
	EXPECT_CALL(*gl, glUniformBlockBinding(programId,address,bufferBindingPoint)).Times(1);
	ubo.attachBuffer(buffer);
}

TEST_F(variable, ssbo_attach_buffer){
	ogl::Buffer_Block ssbo{{address, GL_SHADER_STORAGE_BLOCK, programId}, gl};
	EXPECT_CALL(*buffer, bindingPoint()).WillOnce(Return(bufferBindingPoint));
	EXPECT_CALL(*gl, glShaderStorageBlockBinding(programId,address,bufferBindingPoint)).Times(1);
	ssbo.attachBuffer(buffer);
}

