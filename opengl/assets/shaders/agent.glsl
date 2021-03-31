#version 460

layout(local_size_x = 1 /*, local_size_y = 1*/) in;
layout(rgba32f, binding = 0) uniform image2D utexture;

uniform float udelta;
uniform int uwidth;
uniform int uheight;
uniform float uspeed;

uint
hash(uint state)
{
    state ^= 2747636419u;
    state *= 2654435769u;
    state ^= state >> 16;
    state *= 2654435769u;
    state ^= state >> 16;
    state *= 2654435769u;
    return state;
}

float
scale(uint state)
{
    return state / 4294967295.0;
}

struct Agent
{
    vec2  position;
    float angle;
    float dump;
};

layout (std430, binding = 1) buffer Agents
{
    Agent agents[];
};

float
sense(Agent agent, float off)
{
    int dst   = 10; /* TODO: make uniform? */
    int ssize = 5;
    float angle  = agent.angle + off;
    vec2 dir     = vec2(cos(angle), sin(angle));
    ivec2 center = ivec2(agent.position + dir * dst);

    float sum = 0.0f;
    for (int offx = -ssize; offx <= ssize; offx++) {
        for (int offy = -ssize; offy <= ssize; offy++) {
            ivec2 pos = center + ivec2(offx, offy);
            if (pos.x >= 0 && pos.x < uwidth && pos.y >= 0 && pos.y < uheight) {
                sum += imageLoad(utexture, pos).x;
            }
        }
    }
    return sum;
}

void
main()
{
    // base pixel colour for image

    
    // get index in global work group i.e x,y position
    // ivec2 id = ivec2(gl_GlobalInvocationID.xy);
    ivec2 d = ivec2(gl_GlobalInvocationID.xy);
    uint id = d.x; //gl_GlobalInvocationID.x;
    //if (id > 5000) return;

    vec4 data = imageLoad(utexture, d);

    // if (id.x < 3) { 
    // if (id < 10) {
    Agent agent = agents[id];
    uint random = hash(uint(agent.position.y * uwidth + agent.position.x * uheight));
    // uint random = hash(uint(agent.position.y * uwidth + agent.position.x));

    vec2 direction = vec2(cos(agent.angle), sin(agent.angle));
    vec2 newpos = agent.position + direction * uspeed * udelta;

    float spacing = 0.1f;
    float turnspeed = 1.0f;
    float wfwd  = sense(agent, 0.0f);
    float wleft = sense(agent, spacing);
    float wrght = sense(agent, -spacing);
    float str = scale(random);

    if (wfwd > wleft && wfwd > wrght) {
        agents[id].angle += 0.0f;
    }
    else if (wfwd < wleft && wfwd < wrght) {
        agents[id].angle += (str - 0.5f) * 2.0f * turnspeed * udelta;
    }
    else if (wrght > wleft) {
        agents[id].angle -= str * turnspeed * udelta;
    }
    else if (wleft > wrght) {
        agents[id].angle += str * turnspeed * udelta;
    }

    if (newpos.x < 0 || newpos.x >= uwidth || newpos.y < 0 || newpos.y >= uheight) {
        newpos.x = min(uwidth - 0.01f, max(0.0f, newpos.x));
        newpos.y = min(uheight - 0.01f, max(0.0f, newpos.y));
        // newpos.x = 128;
        // newpos.y = 128;
        // agents[id].angle -= 3.14f;
        agents[id].angle = scale(random) * 2.0f * 3.1415926535f;
    }

    // output to a specific pixel in the image
    agents[id].position = newpos;
    imageStore(utexture, ivec2(newpos), vec4(1.0f));
    // }

    // vec4 sum = vec4(0.0f);
    // for (int offx = -1; offx <= 1; offx++) {
    //     for (int offy = -1; offy <= 1; offy++) {
    //         int samplex = d.x + offx;
    //         int sampley = d.y + offy;
    //         if (samplex >= 0 && samplex < uwidth && sampley >= 0 && sampley < uheight) {
    //             sum += imageLoad(utexture, ivec2(samplex, sampley));
    //         }
    //     }
    // }
    // sum /= 9.0f;
    // data = mix(data, sum, 0.1f * udelta);
    // data = max(vec4(0.0f), data - 0.1f * udelta);

    imageStore(utexture, d, data);
}