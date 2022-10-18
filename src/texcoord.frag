#version 450
#extension GL_ARB_separate_shader_objects : enable

layout (location = 0) in vec3 frag_color;
layout (location = 1) in vec2 frag_texcoord;

layout (binding = 1) uniform sampler2D tex_2d;

layout(location = 0) out vec4 outColor;

void main() {
    outColor = texture(tex_2d, frag_texcoord);
    //outColor = vec4(frag_texcoord, 0.0, 1.0);
}
