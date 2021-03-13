#version 460 core

out vec4 color;

uniform vec4 objcolor;

void
main()
{
    color = objcolor;
}