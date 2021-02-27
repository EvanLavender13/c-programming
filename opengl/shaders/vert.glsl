#version 460 core

in vec3 pos;
in vec3 incolor;

out vec3 outcolor;

void
main()
{
    gl_Position = vec4(pos, 1.0);
    outcolor = incolor;
}