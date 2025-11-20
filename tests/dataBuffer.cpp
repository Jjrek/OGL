#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include "dataBuffer.hpp"
#include "log.hpp"

#include "GLInterfaceMock.hpp"

using ::testing::StrictMock;
using ::testing::_;

using std::any;

constexpr int sint = sizeof(int);
constexpr GLuint bufferId = 2;

class dataBuffer: public testing::Test{
	protected:
		std::shared_ptr<GLMock> gl;

		dataBuffer(){
			ogl::Log::Handle().setLoggingFlags(ogl::LogType::NONE);
			gl = std::make_shared<StrictMock<GLMock>>();
		}

		void expectCreationAndDestructionTimes(int times = 1){
			auto returnBuffer = [](GLuint, GLuint* param){*param = bufferId;};
			EXPECT_CALL(*gl, glCreateBuffers(1,_)).Times(times).WillRepeatedly(returnBuffer);
			auto assertBuffer = [](GLuint, GLuint* param){EXPECT_EQ(*param,bufferId);};
			EXPECT_CALL(*gl, glDeleteBuffers(1,_)).Times(times).WillRepeatedly(assertBuffer);
		}

		void expectBufferPassed(void* buffer, size_t size){
			EXPECT_CALL(*gl, glNamedBufferData(bufferId,size,_,_)).WillOnce(
					[=](any,long size,const void* ptr,any){EXPECT_TRUE(memcmp(buffer,ptr,size)==0);});
		}

		void expectBufferPassed(void* buffer, size_t size, size_t offset){
			EXPECT_CALL(*gl, glNamedBufferSubData(bufferId,offset,size,_)).WillOnce(
					[=](any,any,long size,const void* ptr){EXPECT_TRUE(memcmp(buffer,ptr,size)==0);});
		}
};

TEST_F(dataBuffer, creation){
	expectCreationAndDestructionTimes();
	ogl::DataBuffer buffer(gl);
}

TEST_F(dataBuffer, binding_point_initialized_and_kept){
	expectCreationAndDestructionTimes(3);
	ogl::DataBuffer buffer_bindig_point_0(gl);
	ogl::DataBuffer buffer_bindig_point_1(gl);
	ogl::DataBuffer buffer_bindig_point_2(gl);
	EXPECT_EQ(buffer_bindig_point_0.bindingPoint(), 0);
	EXPECT_EQ(buffer_bindig_point_1.bindingPoint(), 1);
	EXPECT_EQ(buffer_bindig_point_2.bindingPoint(), 2);
	EXPECT_EQ(buffer_bindig_point_0.bindingPoint(), 0);
	EXPECT_EQ(buffer_bindig_point_1.bindingPoint(), 1);
	EXPECT_EQ(buffer_bindig_point_2.bindingPoint(), 2);
}

TEST_F(dataBuffer, pass_to_buffer){
	expectCreationAndDestructionTimes();
	ogl::DataBuffer buffer(gl);

	int arr[3] = {1,2,3};
	expectBufferPassed(arr, sint*3);
	buffer.pass(arr, sint*3);
	EXPECT_EQ(buffer.size(), sint*0);
}

TEST_F(dataBuffer, pass_to_buffer_at_offset){
	expectCreationAndDestructionTimes();
	ogl::DataBuffer buffer(gl);

	int arr[3] = {1,2,3};
	expectBufferPassed(arr, sint*3, 12);
	buffer.pass(arr, sint*3, 12);
	EXPECT_EQ(buffer.size(), sint*0);
}

TEST_F(dataBuffer, temp_buffer_filling){
	expectCreationAndDestructionTimes();
	ogl::DataBuffer buffer(gl);

	int arr[9] = {1,2,3,4,5,6,7,8,9};
	buffer.feed(arr, sint*3);
	buffer.feed(arr+3, sint);
	buffer.feed(arr+6, sint*3);
	buffer.feed(arr+4, sint*3, sint*4);

	expectBufferPassed(arr, sint*7);
	buffer.push();
	EXPECT_EQ(buffer.size(), sint*7);
}

TEST_F(dataBuffer, temp_buffer_clear){
	expectCreationAndDestructionTimes();
	ogl::DataBuffer buffer(gl);

	int arr[6] = {1,2,3,4,5,6};
	buffer.feed(arr, sint*3);
	buffer.clear();
	buffer.feed(arr+3, sint*3);

	expectBufferPassed(arr+3, sint*3);
	buffer.push();
	EXPECT_EQ(buffer.size(), sint*3);
}

