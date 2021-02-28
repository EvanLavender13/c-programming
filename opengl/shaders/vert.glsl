#version 460 core

in vec3 position;
in vec2 texcoord;

out vec2 outtexcoord;

uniform mat4 projection;
uniform mat4 modelview;

void
main()
{
    gl_Position = projection * modelview * vec4(position, 1.0);
    outtexcoord = texcoord;
}