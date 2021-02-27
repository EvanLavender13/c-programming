#version 460 core

in vec3 outcolor;
out vec4 fragcolor;

void
main()
{
    fragcolor = vec4(outcolor, 1.0);
}