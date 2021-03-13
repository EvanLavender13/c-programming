#version 460 core

in vec3 position;
in vec3 normal;

uniform mat4 tmvp;

void
main()
{
    gl_Position = tmvp * vec4(position, 1.0);
}