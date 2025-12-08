#version 430 core

in vec3 positionToFragment;

layout(std140) uniform colorBuffer{
	vec3 objectColor;
};

out vec4 color;

void main(){
	color = vec4(objectColor*(0.2f*length(positionToFragment)), 1.0f);
}

