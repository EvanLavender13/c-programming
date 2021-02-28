#version 460 core

in vec2 outtexcoord;
out vec4 fragcolor;

uniform sampler2D sampler;

void
main()
{
    fragcolor = texture(sampler, outtexcoord);
}