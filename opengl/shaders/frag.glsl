#version 460 core

in vec4 fragcolor;

// in vec2 outtexcoord;
out vec4 color;

// uniform sampler2D sampler;
// uniform vec3 color;
// uniform int usecolor;

void
main()
{
    color = fragcolor;
    // if (usecolor == 1)
    //     fragcolor = vec4(color, 1);
    // else
    //     fragcolor = texture(sampler, outtexcoord);
}