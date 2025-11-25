#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include "wrappers/program.hpp"
#include "log.hpp"

#include "GLInterfaceMock.hpp"
#include "shaderMock.hpp"
#include "objectFactoryMock.hpp"

using ::testing::StrictMock;
using ::testing::_;
using ::testing::Return;

using std::string;
using std::any;

constexpr GLuint programId = 3;

constexpr GLuint shader1Id = 5;
constexpr GLuint shader2Id = 6;

constexpr GLuint VAO = 8;

struct varParams{
	string name;
	GLint type;
	GLint location;
};
constexpr varParams uniform = {"uVariable",GL_FLOAT,10};
constexpr varParams attribute = {"aVariable",GL_FLOAT,11};
constexpr varParams UBO = {"ubo",GL_FLOAT,12};
constexpr varParams SSBO = {"ssbo",GL_FLOAT,13};

class program: public testing::Test{
	protected:
		std::shared_ptr<ShaderMock> shader1;
		std::shared_ptr<ShaderMock> shader2;
		std::shared_ptr<GLMock> gl;
		std::shared_ptr<ogl::Program> testProgram;

		program(){
			ogl::Log::Handle().setLoggingFlags(ogl::LogType::NONE);
			shader1 = std::make_shared<StrictMock<ShaderMock>>();
			shader2 = std::make_shared<StrictMock<ShaderMock>>();
			gl = std::make_shared<StrictMock<GLMock>>();
			expectCreationAndDestruction();
		}

		void expectCreationAndDestruction(){
			EXPECT_CALL(*gl, glCreateProgram()).WillOnce(Return(programId));
			EXPECT_CALL(*gl, glDeleteProgram(programId)).Times(1);
		}

		void building(){
			EXPECT_CALL(*shader1, id()).Times(2).WillRepeatedly(Return(shader1Id));
			EXPECT_CALL(*shader2, id()).Times(2).WillRepeatedly(Return(shader2Id));
			EXPECT_CALL(*gl, glAttachShader(programId, shader1Id)).Times(1);
			EXPECT_CALL(*gl, glAttachShader(programId, shader2Id)).Times(1);
			EXPECT_CALL(*gl, glLinkProgram(programId)).Times(1);
			EXPECT_CALL(*gl, glDetachShader(programId, shader1Id)).Times(1);
			EXPECT_CALL(*gl, glDetachShader(programId, shader2Id)).Times(1);
		}

		static void returnParameters(GLint* parameters, varParams variable){
			GLint params[3] = {static_cast<GLint>(variable.name.length()+1),variable.type,variable.location};
			memcpy(parameters, params, sizeof(GLint)*3);}
		void pollInfo(GLenum type, varParams variable){
			EXPECT_CALL(*gl, glGetProgramInterfaceiv(programId,type,_,_)).WillOnce(
					[](any,any,any,GLint* count){*count = 1;});
			EXPECT_CALL(*gl, glGetProgramResourceiv(programId,type,_,_,_,_,_,_)).WillOnce(
					[=](any,any,any,any,any,any,any,GLint* parameters){returnParameters(parameters,variable);});
			EXPECT_CALL(*gl, glGetProgramResourceName(programId,type,_,_,_,_)).WillOnce(
					[=](any,any,any,any,any,GLchar* name){memcpy(name, variable.name.c_str(), variable.name.length()+1);});
		}

		void create(){
			ObjectFactoryMock factory;
			testProgram = factory.createPointer<ogl::Program>(gl);
		}

		void succesfulBuild(){
			building();
			auto returnSucces = [](GLuint, GLenum, GLint* param){*param = 1;};
			EXPECT_CALL(*gl, glGetProgramiv(programId, GL_LINK_STATUS, _)).WillOnce(returnSucces);
			EXPECT_CALL(*gl, glUseProgram(programId)).Times(1);
			auto returnVAO = [](GLuint, GLuint* param){*param = VAO;};
			EXPECT_CALL(*gl, glGenVertexArrays(1,_)).WillOnce(returnVAO);
			EXPECT_CALL(*gl, glBindVertexArray(VAO)).Times(1);
			pollInfo(GL_UNIFORM, uniform);
			pollInfo(GL_PROGRAM_INPUT, attribute);
			EXPECT_CALL(*gl, glEnableVertexAttribArray(attribute.location));
			pollInfo(GL_UNIFORM_BLOCK, UBO);
			EXPECT_CALL(*gl, glGetUniformBlockIndex(programId,_)).WillOnce(Return(UBO.location));
			pollInfo(GL_SHADER_STORAGE_BLOCK, SSBO);
			EXPECT_CALL(*gl, glGetProgramResourceIndex(programId,GL_SHADER_STORAGE_BLOCK,_)).WillOnce(Return(SSBO.location));
			auto assertVAO = [](GLuint, GLuint* param){EXPECT_EQ(*param,VAO);};
			EXPECT_CALL(*gl, glDeleteVertexArrays(1,_)).WillOnce(assertVAO);
			create();
		}

		void failedBuild(){
			building();
			auto returnFail = [](GLuint, GLenum, GLint* param){*param = 0;};
			EXPECT_CALL(*gl, glGetProgramiv(programId, GL_LINK_STATUS, _)).WillOnce(returnFail);

			const string info{"Program fail msg."};
			unsigned il = info.length()+1;
			auto returnInfoLength = [=](GLuint, GLenum, GLint* param){*param = il;};
			EXPECT_CALL(*gl, glGetProgramiv(programId, GL_INFO_LOG_LENGTH, _)).WillOnce(returnInfoLength);
			auto returnInfo = [=](GLuint, GLsizei len, GLsizei*, GLchar* text)
				{memcpy(text, info.c_str(), fmin(il, len));};
			EXPECT_CALL(*gl, glGetProgramInfoLog(programId, il, _, _)).WillOnce(returnInfo);
			create();
		}
};

TEST_F(program, building_failure){
	failedBuild();
	testProgram->build({shader1, shader2});
	EXPECT_EQ(static_cast<bool>(*testProgram), false);
}

TEST_F(program, building_succes){
	succesfulBuild();
	testProgram->build({shader1, shader2});
	EXPECT_EQ(static_cast<bool>(*testProgram), true);
}

TEST_F(program, activation){
	succesfulBuild();
	EXPECT_CALL(*gl, glUseProgram(programId)).Times(1).RetiresOnSaturation();
	EXPECT_CALL(*gl, glBindVertexArray(VAO)).Times(1).RetiresOnSaturation();
	testProgram->build({shader1, shader2});
	testProgram->activate();
}

TEST_F(program, variable_get_uniform){
	succesfulBuild();
	testProgram->build({shader1, shader2});
	EXPECT_GT(testProgram->get(uniform.name).use_count(), 0);
}

TEST_F(program, variable_get_attribute){
	succesfulBuild();
	testProgram->build({shader1, shader2});
	EXPECT_GT(testProgram->get(attribute.name).use_count(), 0);
}

TEST_F(program, variable_get_ubo){
	succesfulBuild();
	testProgram->build({shader1, shader2});
	EXPECT_GT(testProgram->get(UBO.name).use_count(), 0);
}

TEST_F(program, variable_get_ssbo){
	succesfulBuild();
	testProgram->build({shader1, shader2});
	EXPECT_GT(testProgram->get(SSBO.name).use_count(), 0);
}

TEST_F(program, variable_get_fail){
	succesfulBuild();
	testProgram->build({shader1, shader2});
	EXPECT_EQ(testProgram->get("nonexistingname").use_count(), 0);
}

