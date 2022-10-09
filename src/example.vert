#version 450
#extension GL_ARB_separate_shader_objects : enable

layout (location = 0) in vec3 position;
layout(binding = 0) uniform camera {
	mat4 v;
	mat4 p;
} mvp;

layout(location = 0) out vec3 fragColor;

void main() {
    gl_Position = mvp.p * mvp.v * vec4(position, 1.0);
    fragColor = vec3(1.0, 1.0, 1.0); //color;
}
