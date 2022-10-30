#version 450
#extension GL_ARB_separate_shader_objects : enable

layout (location = 0) in vec3 position;
layout (location = 1) in vec2 texcoord;

layout (location = 2) in mat4 model_matrix;

layout (binding = 0) uniform camera {
	mat4 v;
	mat4 p;
} mvp;

layout (location = 0) out vec3 frag_position;
layout (location = 1) out vec2 frag_texcoord;

void main() {
    gl_Position = mvp.p * mvp.v * model_matrix * vec4(position, 1.0);
    frag_position = gl_Position.xyz;
    frag_texcoord = texcoord;
}
