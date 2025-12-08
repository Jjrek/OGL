#version 430 core

in vec3 position;

uniform mat4 PV;

uniform int transformIndex; 
layout(std430)buffer location{
	mat4 transform[4];
};

out vec3 positionToFragment;

void main(){
	positionToFragment = position;
	gl_Position = PV*transform[transformIndex]*vec4(position, 1.0f);
}

