#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include "shader.hpp"

#include "GLInterfaceMock.hpp"
#include "log.hpp"

#include <memory>
#include <string>

using ::testing::StrictMock;
using ::testing::_;
using ::testing::Return;
using ::testing::Invoke;

using std::unique_ptr;
using std::string;

const string line1 = "line1\n";
const string line2 = "line2\n";
const string line3 = "line3\n";

constexpr GLenum shaderType = GL_VERTEX_SHADER;
constexpr GLuint shaderId = 3;

class shaders: public testing::Test{
	protected:

		std::unique_ptr<ogl::Shader> shader;
		std::unique_ptr<GLMock> gl;

		shaders():gl(std::make_unique<StrictMock<GLMock>>()){
			ogl::Log::Handle().setLoggingFlags(ogl::LogType::NONE);
		}

		void createShader(const string code, const std::set<std::string>& compileFlags){
			shader = std::make_unique<ogl::Shader>(shaderType, code, compileFlags, std::move(gl));
		};

		void init(const string code, const std::set<std::string>& compileFlags){
			expectShaderInitializationAndDestruction();
			shaderInitializationSucces();
			createShader(code, compileFlags);
		}

		void expectShaderInitializationAndDestruction(){
			EXPECT_CALL(*gl, glCreateShader(shaderType)).WillOnce(Return(shaderId));
			EXPECT_CALL(*gl, glShaderSource(shaderId,_)).Times(1);
			EXPECT_CALL(*gl, glCompileShader(shaderId)).Times(1);
			EXPECT_CALL(*gl, glDeleteShader(shaderId)).Times(1);
		}

		void shaderInitializationSucces(){
			auto returnSucces = [](GLuint, GLenum, GLint* param){*param = 1;};
			EXPECT_CALL(*gl, glGetShaderiv(shaderId, GL_COMPILE_STATUS, _)).WillOnce(Invoke(returnSucces));
		}

		void expectMiddleLineDropped(){
			EXPECT_EQ(shader->code(), line1+line3);
		}

		void expectMiddleLineKept(){
			EXPECT_EQ(shader->code(), line1+line2+line3);
		}
};


const string basicFlagCode =
	line1+
	"@flag\n"+
	line2+
	"@!flag\n"+
	line3;

TEST_F(shaders, empty_flags){
	init(basicFlagCode, {});
	expectMiddleLineDropped();
}

TEST_F(shaders, matching_flag){
	init(basicFlagCode, {"flag"});
	expectMiddleLineKept();
}

TEST_F(shaders, not_matching_flag){
	init(basicFlagCode, {"wrongflag"});
	expectMiddleLineDropped();
}


const string flagsOrCode =
	line1+
	"@flag flag2 flag3\n"+
	line2+
	"@!flag flag2 flag3\n"+
	line3;

TEST_F(shaders, or_of_flags_first_matches){
	init(flagsOrCode, {"flag"});
	expectMiddleLineKept();
}

TEST_F(shaders, or_of_flags_middle_matches){
	init(flagsOrCode, {"flag2"});
	expectMiddleLineKept();
}

TEST_F(shaders, or_of_flags_last_matches){
	init(flagsOrCode, {"flag3"});
	expectMiddleLineKept();
}

TEST_F(shaders, or_of_flags_multiple_matches){
	init(flagsOrCode, {"flag1","flag3"});
	expectMiddleLineKept();
}

TEST_F(shaders, or_of_flags_non_matches){
	init(flagsOrCode, {"flag4"});
	expectMiddleLineDropped();
}


const string flagDifferentOrderCode =
	line1+
	"@flag flag2\n"+
	line2+
	"@!flag2 flag\n"+
	line3;

TEST_F(shaders, different_order_flag_matches){
	init(flagDifferentOrderCode, {"flag"});
	expectMiddleLineKept();
}

TEST_F(shaders, different_order_flag_not_matches){
	init(flagDifferentOrderCode, {"flag3"});
	expectMiddleLineDropped();
}


const string flagNegationCode =
	line1+
	"@~flag\n"+
	line2+
	"@!~flag\n"+
	line3;

TEST_F(shaders, flag_negation_empty_flags){
	init(flagNegationCode, {});
	expectMiddleLineKept();
}

TEST_F(shaders, flag_negation_flag_not_exists){
	init(flagNegationCode, {"flag1"});
	expectMiddleLineKept();
}

TEST_F(shaders, flag_negation_flag_exists){
	init(flagNegationCode, {"flag"});
	expectMiddleLineDropped();
}


const string flagNegationWithOtherFlagCode =
	line1+
	"@~flag flag2\n"+
	line2+
	"@!~flag flag2\n"+
	line3;

TEST_F(shaders, flag_negation_with_other_empty_flags){
	init(flagNegationWithOtherFlagCode, {});
	expectMiddleLineKept();
}

TEST_F(shaders, flag_negation_with_other_negated_matches){
	init(flagNegationWithOtherFlagCode, {"flag"});
	expectMiddleLineDropped();
}

TEST_F(shaders, flag_negation_with_other_non_negated_matches){
	init(flagNegationWithOtherFlagCode, {"flag2"});
	expectMiddleLineKept();
}

TEST_F(shaders, flag_negation_with_other_both_matches){
	init(flagNegationWithOtherFlagCode, {"flag","flag2"});
	expectMiddleLineKept();
}

TEST_F(shaders, flag_negation_with_other_non_matches){
	init(flagNegationCode, {"flag3"});
	expectMiddleLineKept();
}






class shadersIllformed: public shaders{
	protected:

		void init(const string code, const std::set<std::string>& compileFlags){
			expectShaderInitializationAndDestruction();
			shaderInitializationFail();
			shaderInitializationFailHandling();
			createShader(code, compileFlags);
		}

		void shaderInitializationFail(){
			auto returnFail = [](GLuint, GLenum, GLint* param){*param = 0;};
			EXPECT_CALL(*gl, glGetShaderiv(shaderId, GL_COMPILE_STATUS, _)).WillOnce(Invoke(returnFail));
		}

		void shaderInitializationFailHandling(){
			const string info{"Shader fail msg."};
			unsigned il = info.length()+1;
			auto returnInfoLength = [=](GLuint, GLenum, GLint* param){*param = il;};
			EXPECT_CALL(*gl, glGetShaderiv(shaderId, GL_INFO_LOG_LENGTH, _)).WillOnce(Invoke(returnInfoLength));
			auto returnInfo = [=](GLuint, GLsizei len, GLsizei*, GLchar* text)
				{memcpy(text, info.c_str(), fmin(il, len));};
			EXPECT_CALL(*gl, glGetShaderInfoLog(shaderId, il, _, _)).WillOnce(Invoke(returnInfo));

			const string src{"Src code. \nSecond line."};
			unsigned sl = src.length()+1;
			auto returnSrcLength = [=](GLuint, GLenum, GLint* param){*param = sl;};
			EXPECT_CALL(*gl, glGetShaderiv(shaderId, GL_SHADER_SOURCE_LENGTH, _)).WillOnce(Invoke(returnSrcLength));
			auto returnSrc = [=](GLuint, GLsizei len, GLsizei*, GLchar* text)
				{memcpy(text, src.c_str(), fmin(sl, len));};
			EXPECT_CALL(*gl, glGetShaderSource(shaderId, sl, _, _)).WillOnce(Invoke(returnSrc));
		}

		void expectShaderBeingIncomplete(){
			EXPECT_EQ(static_cast<bool>(*shader), false);
		}

};


const string blockMismatchCode =
	line1+
	"@flag flag2\n"+
	line2+
	"@!flag3\n"+
	line3;

TEST_F(shadersIllformed, block_mismatch_openning_matches){
	createShader(blockMismatchCode, {"flag"});
	expectShaderBeingIncomplete();
}

TEST_F(shadersIllformed, block_mismatch_openning_not_matches){
	createShader(blockMismatchCode, {"flag4"});
	expectShaderBeingIncomplete();
}


const string blockInterleavedCode =
	line1+
	"@flag flag2\n"+
	"@flag3\n"+
	line2+
	"@!flag flag2\n"+
	"@!flag3\n"+
	line3;

TEST_F(shadersIllformed, block_interleaved_first_matches){
	createShader(blockInterleavedCode, {"flag"});
	expectShaderBeingIncomplete();
}

TEST_F(shadersIllformed, block_interleaved_second_matches){
	createShader(blockInterleavedCode, {"flag3"});
	expectShaderBeingIncomplete();
}

TEST_F(shadersIllformed, block_interleaved_non_matches){
	createShader(blockInterleavedCode, {"flag4"});
	expectShaderBeingIncomplete();
}

TEST_F(shadersIllformed, compilation_failure){
	init(basicFlagCode, {});
	expectShaderBeingIncomplete();
}

