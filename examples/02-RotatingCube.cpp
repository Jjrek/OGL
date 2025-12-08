#include "log.hpp"
#include "ogl.hpp"
#include "constants.hpp"

#include <ranges>

using ogl::LogType;

using std::shared_ptr;

void createShaders(ogl::Program& program, shared_ptr<ogl::ObjectFactory> factory){
	program.build({factory->createPointer<ogl::ShaderFromFile>(
							GL_VERTEX_SHADER, "./shaders/02/vertex.glsl"),
					factory->createPointer<ogl::ShaderFromFile>(
							GL_FRAGMENT_SHADER, "./shaders/02/fragment.glsl")});
}

struct DataBuffers{
	shared_ptr<ogl::DataBuffer> positions;
	shared_ptr<ogl::DataBuffer> indices;
	shared_ptr<ogl::DataBuffer> color;
	shared_ptr<ogl::DataBuffer> location;
};

DataBuffers createBuffers(ogl::Program& program, shared_ptr<ogl::ObjectFactory> factory){
	shared_ptr<ogl::DataBuffer> positions = factory->createPointer<ogl::DataBuffer>();
	positions->pass<float>(cubeCorners);
	if(auto ptr = program.get<ogl::Attribute>("position"))
		ptr->attachBuffer(positions);

	shared_ptr<ogl::DataBuffer> indices = factory->createPointer<ogl::DataBuffer>();
	indices->pass<unsigned char>(cubeIndices);
	indices->bind(GL_ELEMENT_ARRAY_BUFFER);

	shared_ptr<ogl::DataBuffer> color = factory->createPointer<ogl::DataBuffer>();
	color->pass<float>({0.4f,1,0.4f});
	if(auto ptr = program.get<ogl::Buffer_Block>("colorBuffer"))
		ptr->attachBuffer(color);

	if(auto ptr = program.get<ogl::Uniform>("PV")) ptr->pass(PVfromCorner.data());

	shared_ptr<ogl::DataBuffer> location = factory->createPointer<ogl::DataBuffer>();
	location->pass(rotations);
	if(auto ptr = program.get<ogl::Buffer_Block>("location"))
		ptr->attachBuffer(location);

	return{positions, indices, color, location};
}

int main(){
	ogl::Log::Handle().setLoggingFlags(LogType::ERROR|LogType::WRN);
	ogl::Ogl context;
	if(!context){
		LOG(LogType::ERROR)<<"Initialization failed, ending\n";
		return 1;
	}
	shared_ptr<ogl::ObjectFactory> factory = context.factory();
	ogl::Program program = factory->create<ogl::Program>();

	createShaders(program, factory);
	DataBuffers dataBuffers = createBuffers(program, factory);

	glEnable(GL_DEPTH_TEST);
	glClearColor(0.05,0.05,0.05,1);

	if(auto transformIndex = program.get<ogl::Uniform>("transformIndex"))
	for(int i : std::views::iota(0,33)){
		int index = i%4;
		transformIndex->pass(&index);
		glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
		glDrawElements(GL_TRIANGLES, cubeIndices.size(), GL_UNSIGNED_BYTE, nullptr);
		context.window()->swap();
		usleep(75000);
	}

	return 0;
}

