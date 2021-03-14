#version 460 core

out vec4 color;

uniform vec4 uobjcolor;

void
main()
{
    color = uobjcolor;
}