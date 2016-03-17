#version 150
in vec2 position;
in vec2 texcoord;

uniform mat4 projection;
uniform mat4 view;
uniform mat4 model;

out vec2 frag_tex;

void main()
{
    gl_Position = projection * view * vec4(position, 0.0, 1.0);
    frag_tex = texcoord;
}