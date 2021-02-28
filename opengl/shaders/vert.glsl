#version 460 core

in vec3 position;
in vec2 texcoord;

out vec2 outtexcoord;

uniform mat4 projection;
uniform mat4 world;

void
main()
{
    gl_Position = projection * world * vec4(position, 1.0);
    outtexcoord = texcoord;
}