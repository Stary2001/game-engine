#version 150 

in vec2 texcoord;

uniform sampler2D tex;
out vec4 outColor;


void main()
{
    outColor = vec4(1.0, 1.0, 1.0, 1.0) * texture(tex, texcoord);
}