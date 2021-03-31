#version 460 core

in vec3 outnormal;   /* from vert.glsl */
in vec2 outtexcoord; /* from vert.glsl */

out vec4 color;

uniform vec4 uobjcolor;
uniform sampler2D utexture;

void
main()
{
    // color = uobjcolor;
    color = texture(utexture, outtexcoord);
}