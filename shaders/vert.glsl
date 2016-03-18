#version 150

in vec3 position;
in vec2 texcoord;

uniform mat4 projection;
uniform mat4 view;
uniform mat4 model;

out vec2 frag_tex;

void main()
{
    gl_Position = projection * view * model * vec4(position, 1.0);
    frag_tex = texcoord;
}