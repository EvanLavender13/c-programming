#version 460 core

in vec3 position;
in vec3 incolor;

out vec3 outcolor;

uniform mat4 projection;

void
main()
{
    gl_Position = projection * vec4(position, 1.0);
    outcolor = incolor;
}