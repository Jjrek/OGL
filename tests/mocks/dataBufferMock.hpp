#ifndef INCLUDE_DATA_BUFFER_MOCK_HPP_
#define INCLUDE_DATA_BUFFER_MOCK_HPP_

#include <gmock/gmock.h>

#include "wrappers/dataBuffer.hpp"
#include "GLInterfaceMock.hpp"

class DataBufferMock : public ogl::DataBuffer{
	public:
		DataBufferMock():DataBuffer(std::make_unique<testing::NiceMock<GLMock>>()){};
		MOCK_METHOD(GLuint, id, (), (override));
		MOCK_METHOD(unsigned, bindingPoint, (GLenum target), (override));
};

#endif // INCLUDE_DATA_BUFFER_MOCK_HPP_
