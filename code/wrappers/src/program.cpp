#include "program.hpp"
#include "log.hpp"

#include <memory>
#include <vector>

using std::shared_ptr;
using std::vector;

namespace ogl{

Program::Program(std::unique_ptr<GLInterface> interface)
	noexcept:gl(std::move(interface)){

	isValid = false;
	id = gl->glCreateProgram();
}

Program::~Program(){
	gl->glDeleteProgram(id);
}

bool Program::build(const vector<shared_ptr<Shader>>& shaders){

	for(auto shader: shaders){
		gl->glAttachShader(id, shader->getId());
	}

	gl->glLinkProgram(id);

	for(auto shader: shaders){
		gl->glDetachShader(id, shader->getId());
	}

	GLint succes;
	gl->glGetProgramiv(id, GL_LINK_STATUS, &succes);
	if(!succes){
		GLint length;
		gl->glGetProgramiv(id, GL_INFO_LOG_LENGTH, &length);
		vector<char> info(length);
		gl->glGetProgramInfoLog(id, length, &length, info.data());
		LOG(LogType::ERROR)<<info.data()<<"\n";
		return false;
	}

	isValid = true;

	gl->glUseProgram(id);
	gl->glGenVertexArrays(1, &vertexArrayID);
	gl->glBindVertexArray(vertexArrayID);

	return true;
}

void Program::use(){
	gl->glUseProgram(id);
	gl->glBindVertexArray(vertexArrayID);
}

}
