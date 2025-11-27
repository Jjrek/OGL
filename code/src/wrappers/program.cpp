#include "wrappers/program.hpp"
#include "log.hpp"

#include <memory>
#include <vector>
#include <string>

using std::shared_ptr;
using std::make_shared;
using std::vector;
using std::string;

namespace ogl{

	Program::Program(std::shared_ptr<GLInterface> interface)noexcept{
		gl = interface;
		isValid = false;
		id = gl->glCreateProgram();
		vertexArrayID = 0;
		LOG(LogType::CONSTRUC)<<"program id:"<<id<<"\n";
	}

	Program::~Program(){
		gl->glDeleteProgram(id);
		LOG(LogType::DESTRUCT)<<"program id:"<<id<<"\n";
		if(isValid){
			LOG(LogType::DESTRUCT)<<"vao id:"<<vertexArrayID<<"\n";
			gl->glDeleteVertexArrays(1, &vertexArrayID);
		}
	}

	bool Program::build(const vector<shared_ptr<Shader>>& shaders){

		bool computeProgram = false;
		for(auto shader: shaders){
			if(shader->type() == GL_COMPUTE_SHADER) computeProgram = true;
			unsigned shaderId = shader->id();
			gl->glAttachShader(id, shaderId);
			LOG(LogType::INFO)<<"Attaching shader:"
								<<shaderId
								<<" to program:"
								<<id
								<<"\n";
		}

		gl->glLinkProgram(id);

		for(auto shader: shaders){
			gl->glDetachShader(id, shader->id());
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

		if(!computeProgram){
			gl->glGenVertexArrays(1, &vertexArrayID);
			LOG(LogType::CONSTRUC)<<"vao id:"<<vertexArrayID<<"\n";
		}
		gl->glBindVertexArray(vertexArrayID);

		pollVariables();

		return true;
	}

	void Program::poll(GLenum resourceType, auto factory){
		GLenum propertyEnums[3] = {GL_NAME_LENGTH, GL_TYPE, GL_LOCATION};
		GLint properties[3];
		GLint& nameLen = properties[0];
		GLint& type = properties[1];
		GLint& address = properties[2];
		address = 0;
		int enumCount = (resourceType == GL_UNIFORM || resourceType == GL_PROGRAM_INPUT)?
						3:1;

		GLint count;
		gl->glGetProgramInterfaceiv(id, resourceType, GL_ACTIVE_RESOURCES, &count);
		for(int i = 0; i < count; ++i){
			gl->glGetProgramResourceiv(	id,
									resourceType,
									i,
									enumCount,
									propertyEnums,
									enumCount,
									NULL,
									properties);

			vector<GLchar> name(nameLen);
			gl->glGetProgramResourceName(id,
									resourceType,
									i,
									nameLen,
									&nameLen,
									name.data());
			if(address >= 0){
				string name_s(name.data());
				LOG(LogType::CONSTRUC)<<name_s<<" ";
				variables[name_s] =
					factory(name_s, {static_cast<GLuint>(address), type, id});
			}
		}
	}

	void Program::pollVariables(){
		poll(GL_UNIFORM,
			[this](string, Variable::Params params){
				return make_shared<Uniform>(params, gl);});
		poll(GL_PROGRAM_INPUT,
			[this](string, Variable::Params params){
				return make_shared<Attribute>(params, gl);});
		poll(GL_UNIFORM_BLOCK,
			[this](string name, Variable::Params params){
				return make_shared<Buffer_Block>(Variable::Params{gl->glGetUniformBlockIndex(params.programId, name.c_str()),
													GL_UNIFORM_BLOCK,
													params.programId}, gl);});
		poll(GL_SHADER_STORAGE_BLOCK,
			[this](string name, Variable::Params params){
				return make_shared<Buffer_Block>(Variable::Params{gl->glGetProgramResourceIndex(params.programId, GL_SHADER_STORAGE_BLOCK, name.c_str()),
													GL_SHADER_STORAGE_BLOCK,
													params.programId}, gl);});
	}

	void Program::activate(){
		gl->glUseProgram(id);
		gl->glBindVertexArray(vertexArrayID);
	}

	shared_ptr<Variable> Program::get(string varName){
		if(variables.contains(varName)){
			return variables[varName];
		}else{
			LOG(LogType::WRN)<<"Program "<<id<<" does not contain variable "<<varName<<"\n";
			return {};
		}
	}

}
