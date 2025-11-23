#ifndef INCLUDE_SHADER_MOCK_HPP_
#define INCLUDE_SHADER_MOCK_HPP_

#include <gmock/gmock.h>

#include "shader.hpp"
#include "GLInterfaceMock.hpp"

class ShaderMock: public ogl::Shader{
	public:
		ShaderMock():Shader(GL_VERTEX_SHADER, "dummy", {}, std::make_unique<testing::NiceMock<GLMock>>()){};
		MOCK_METHOD(GLuint, id, (), (const override));

};

#endif // INCLUDE_SHADER_MOCK_HPP_
