#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include "program.hpp"

#include "GLInterfaceMock.hpp"
#include "shaderMock.hpp"
#include "log.hpp"

using ::testing::StrictMock;
using ::testing::_;
using ::testing::Return;
using ::testing::Invoke;

using std::unique_ptr;
using std::string;

constexpr GLuint programId = 3;

constexpr GLuint shader1Id = 5;
constexpr GLuint shader2Id = 6;

constexpr GLuint VAO = 8;

class program: public testing::Test{
	protected:

		std::shared_ptr<ShaderMock> shader1;
		std::shared_ptr<ShaderMock> shader2;
		std::unique_ptr<GLMock> gl;

		program(){
			ogl::Log::Handle().setOutputStream(nullptr);
			shader1 = std::make_shared<StrictMock<ShaderMock>>();
			shader2 = std::make_shared<StrictMock<ShaderMock>>();
			gl = std::make_unique<StrictMock<GLMock>>();
			expectCreationAndDestruction();
		}

		void expectCreationAndDestruction(){
			EXPECT_CALL(*gl, glCreateProgram()).WillOnce(Return(programId));
			EXPECT_CALL(*gl, glDeleteProgram(programId)).Times(1);
		}

		void building(){
			EXPECT_CALL(*shader1, getId()).Times(2).WillRepeatedly(Return(shader1Id));
			EXPECT_CALL(*shader2, getId()).Times(2).WillRepeatedly(Return(shader2Id));
			EXPECT_CALL(*gl, glAttachShader(programId, shader1Id)).Times(1);
			EXPECT_CALL(*gl, glAttachShader(programId, shader2Id)).Times(1);
			EXPECT_CALL(*gl, glLinkProgram(programId)).Times(1);
			EXPECT_CALL(*gl, glDetachShader(programId, shader1Id)).Times(1);
			EXPECT_CALL(*gl, glDetachShader(programId, shader2Id)).Times(1);
		}

		void buildingSucces(){
			building();
			auto returnSucces = [](GLuint, GLenum, GLint* param){*param = 1;};
			EXPECT_CALL(*gl, glGetProgramiv(programId, GL_LINK_STATUS, _)).WillOnce(Invoke(returnSucces));
			EXPECT_CALL(*gl, glUseProgram(programId)).Times(1);
			auto returnVAO = [](GLuint, GLuint* param){*param = VAO;};
			EXPECT_CALL(*gl, glGenVertexArrays(1,_)).WillOnce(Invoke(returnVAO));
			EXPECT_CALL(*gl, glBindVertexArray(VAO)).Times(1);
		}

		void buildingFailure(){
			building();
			auto returnFail = [](GLuint, GLenum, GLint* param){*param = 0;};
			EXPECT_CALL(*gl, glGetProgramiv(programId, GL_LINK_STATUS, _)).WillOnce(Invoke(returnFail));

			const string info{"Program fail msg."};
			unsigned il = info.length()+1;
			auto returnInfoLength = [=](GLuint, GLenum, GLint* param){*param = il;};
			EXPECT_CALL(*gl, glGetProgramiv(programId, GL_INFO_LOG_LENGTH, _)).WillOnce(Invoke(returnInfoLength));
			auto returnInfo = [=](GLuint, GLsizei len, GLsizei*, GLchar* text)
				{memcpy(text, info.c_str(), fmin(il, len));};
			EXPECT_CALL(*gl, glGetProgramInfoLog(programId, il, _, _)).WillOnce(Invoke(returnInfo));
		}

};

TEST_F(program, building_succes){
	buildingSucces();
	ogl::Program p(std::move(gl));
	p.build({shader1, shader2});
	EXPECT_EQ(static_cast<bool>(p), true);
}

TEST_F(program, building_failure){
	buildingFailure();
	ogl::Program p(std::move(gl));
	p.build({shader1, shader2});
	EXPECT_EQ(static_cast<bool>(p), false);
}
