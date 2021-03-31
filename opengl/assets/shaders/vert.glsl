#version 460 core

in vec3 position;
in vec3 normal;
in vec2 texcoord;

out vec3 outnormal;   /* to frag.glsl */
out vec2 outtexcoord; /* to frag.glsl */

uniform mat4 uviewprojection;
uniform mat4 utransform;

void
main()
{
    gl_Position = uviewprojection * utransform * vec4(position, 1.0);
    outnormal = normal;
    outtexcoord = texcoord;
}