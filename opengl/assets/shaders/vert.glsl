#version 460 core

in vec3 position;
//in vec3 normal;

uniform mat4 uviewprojection;
uniform mat4 utransform;

void
main()
{
    gl_Position = uviewprojection * utransform * vec4(position, 1.0);
}