#include "log.hpp"
#include "ogl.hpp"
#include "program.hpp"

using ogl::LogType;
using CompileFlags = ogl::Shader::CompileFlags;

int main(){

	ogl::Log::Handle().setLoggingFlags(LogType::ERROR|LogType::WRN);
	ogl::Ogl context;
	if(!context){
		LOG(LogType::ERROR)<<"Initialization failed, ending\n";
		return 1;
	}
	std::shared_ptr<ogl::ObjectFactory> factory = context.factory();
	ogl::Program program = factory->create<ogl::Program>();

	program.build({factory->createPointer<ogl::ShaderFromFile>(
							GL_VERTEX_SHADER, "./shaders/vertex.glsl"),
					factory->createPointer<ogl::ShaderFromFile>(
							GL_FRAGMENT_SHADER, "./shaders/fragment.glsl")});

	ogl::DataBuffer positions = factory->create<ogl::DataBuffer>();
	constexpr float p = 0.8f;
	positions.pass<float>({-p,-p,0,
							p,-p,0,
							0,p,0});

	if(auto ptr = std::dynamic_pointer_cast<ogl::Buffered>(program.get("position")))
		ptr->attachBuffer(positions);

	glClearColor(0.02,0,0.04,1);
	glClear(GL_COLOR_BUFFER_BIT);
	glDrawArrays(GL_TRIANGLES, 0, 3);
	context.window()->swap();

	sleep(2);
	return 0;
}

