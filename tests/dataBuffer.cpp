#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <objectFactoryMock.hpp>

#include "wrappers/dataBuffer.hpp"
#include "log.hpp"

#include "GLInterfaceMock.hpp"

using ogl::DataBuffer;

using ::testing::StrictMock;
using ::testing::_;

using std::any;

constexpr int sint = sizeof(int);
constexpr GLuint bufferId = 2;

class dataBuffer: public testing::Test{
	protected:
		std::shared_ptr<GLMock> gl;
		std::shared_ptr<DataBuffer> buffer;

		dataBuffer(){
			ogl::Log::Handle().setLoggingFlags(ogl::LogType::NONE);
			gl = std::make_shared<StrictMock<GLMock>>();
		}

		std::shared_ptr<DataBuffer> createBuffer(){
			ObjectFactoryMock factory;
			return factory.createPointer<DataBuffer>(gl);
		}

		void creationAndDestruction(int times = 1){
			auto returnBuffer = [](GLuint, GLuint* param){*param = bufferId;};
			EXPECT_CALL(*gl, glCreateBuffers(1,_)).Times(times).WillRepeatedly(returnBuffer);
			auto assertBuffer = [](GLuint, GLuint* param){EXPECT_EQ(*param,bufferId);};
			EXPECT_CALL(*gl, glDeleteBuffers(1,_)).Times(times).WillRepeatedly(assertBuffer);
			buffer = createBuffer();
		}

		void expectBufferPassed(void* buffer, size_t size){
			EXPECT_CALL(*gl, glNamedBufferData(bufferId,size,_,_)).WillOnce(
					[=](any,long size,const void* ptr,any){EXPECT_TRUE(memcmp(buffer,ptr,size)==0);});
		}

		void expectBufferPassed(void* buffer, size_t size, size_t offset){
			EXPECT_CALL(*gl, glNamedBufferSubData(bufferId,offset,size,_)).WillOnce(
					[=](any,any,long size,const void* ptr){EXPECT_TRUE(memcmp(buffer,ptr,size)==0);});
		}

		void expectBufferBinding(GLenum target, GLuint bindingPoint, GLuint buffer){
			EXPECT_CALL(*gl, glBindBufferBase(target,bindingPoint,buffer)).Times(1);
		}
};

TEST_F(dataBuffer, creation){
	creationAndDestruction();
}

TEST_F(dataBuffer, ubo_and_ssbo_bindings_separation){
	creationAndDestruction(3);
	std::shared_ptr<DataBuffer> buffer1 = createBuffer();
	std::shared_ptr<DataBuffer> buffer2 = createBuffer();
	expectBufferBinding(GL_UNIFORM_BUFFER, 0, buffer->id());
	EXPECT_EQ(buffer->bindingPoint(GL_UNIFORM_BUFFER), 0);
	expectBufferBinding(GL_UNIFORM_BUFFER, 1, buffer2->id());
	EXPECT_EQ(buffer2->bindingPoint(GL_UNIFORM_BUFFER), 1);

	expectBufferBinding(GL_SHADER_STORAGE_BUFFER, 0, buffer1->id());
	EXPECT_EQ(buffer1->bindingPoint(GL_SHADER_STORAGE_BUFFER), 0);
}

TEST_F(dataBuffer, binding_point_initialized_and_kept){
	creationAndDestruction(3);
	std::shared_ptr<DataBuffer> buffer1 = createBuffer();
	std::shared_ptr<DataBuffer> buffer2 = createBuffer();
	expectBufferBinding(GL_UNIFORM_BUFFER, 2, buffer->id());
	EXPECT_EQ(buffer->bindingPoint(GL_UNIFORM_BUFFER), 2);
	expectBufferBinding(GL_UNIFORM_BUFFER, 3, buffer1->id());
	EXPECT_EQ(buffer1->bindingPoint(GL_UNIFORM_BUFFER), 3);
	expectBufferBinding(GL_UNIFORM_BUFFER, 4, buffer2->id());
	EXPECT_EQ(buffer2->bindingPoint(GL_UNIFORM_BUFFER), 4);

	EXPECT_EQ(buffer->bindingPoint(GL_UNIFORM_BUFFER), 2);
	EXPECT_EQ(buffer1->bindingPoint(GL_UNIFORM_BUFFER), 3);
	EXPECT_EQ(buffer2->bindingPoint(GL_UNIFORM_BUFFER), 4);
}

TEST_F(dataBuffer, pass_to_buffer){
	creationAndDestruction();

	int arr[3] = {1,2,3};
	expectBufferPassed(arr, sint*3);
	buffer->pass(arr, sint*3);
	EXPECT_EQ(buffer->size(), sint*0);
}

TEST_F(dataBuffer, pass_to_buffer_at_offset){
	creationAndDestruction();

	int arr[3] = {1,2,3};
	expectBufferPassed(arr, sint*3, 12);
	buffer->pass(arr, sint*3, 12);
	EXPECT_EQ(buffer->size(), sint*0);
}

TEST_F(dataBuffer, temp_buffer_filling){
	creationAndDestruction();

	int arr[9] = {1,2,3,4,5,6,7,8,9};
	buffer->feed(arr, sint*3);
	buffer->feed(arr+3, sint);
	buffer->feed(arr+6, sint*3);
	buffer->feed(arr+4, sint*3, sint*4);

	expectBufferPassed(arr, sint*7);
	buffer->push();
	EXPECT_EQ(buffer->size(), sint*7);
}

TEST_F(dataBuffer, temp_buffer_clear){
	creationAndDestruction();

	int arr[6] = {1,2,3,4,5,6};
	buffer->feed(arr, sint*3);
	buffer->clear();
	buffer->feed(arr+3, sint*3);

	expectBufferPassed(arr+3, sint*3);
	buffer->push();
	EXPECT_EQ(buffer->size(), sint*3);
}

