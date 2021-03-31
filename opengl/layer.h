#ifndef LAYER_H_
#define LAYER_H_

#include <GLFW/glfw3.h>

#include <camera.h>
#include <model.h>
#include <render.h>
#include <shader.h>
#include <things.h>
#include <util.h>

typedef struct Layer Layer;
struct Layer
{
    float aspect;

    Camera     *camera;
    ShaderProg *shaderprog;
    ShaderProg *agentprog;
    ShaderProg *faderprog;
};

/* TODO: move this */
typedef struct Agent Agent;
struct Agent
{
    vec2  position;
    float angle;
    float dump; /* TODO: unused? */
};

Agent *agents;
int numagents = 128 * 500;

void
layerinit(GLFWwindow *w, Layer *layer)
{
    int width, height;

    glfwGetWindowSize(w, &width, &height);
    renderviewport(0, 0, width, height);
    layer->aspect = (float) width / (float) height;

    /* initialize shader program(s) */
    /* TODO: move somewhere */
    layer->shaderprog = memalloc(sizeof(ShaderProg));
    sproginit(layer->shaderprog, "../assets/shaders/vert.glsl", "../assets/shaders/frag.glsl");
    sproglink(layer->shaderprog);
    layer->shaderprog->uviewprojection = glGetUniformLocation(layer->shaderprog->progid, "uviewprojection");
    layer->shaderprog->utransform      = glGetUniformLocation(layer->shaderprog->progid, "utransform");
    layer->shaderprog->uobjcolor       = glGetUniformLocation(layer->shaderprog->progid, "uobjcolor");
    layer->shaderprog->utexture        = glGetUniformLocation(layer->shaderprog->progid, "utexture");

    layer->agentprog  = memalloc(sizeof(ShaderProg));
    sprogcomp(layer->agentprog, "../assets/shaders/agent.glsl");
    sproglink(layer->agentprog);
    layer->agentprog->utexture = glGetUniformLocation(layer->agentprog->progid, "utexture");
    layer->agentprog->udelta   = glGetUniformLocation(layer->agentprog->progid, "udelta");
    layer->agentprog->uwidth   = glGetUniformLocation(layer->agentprog->progid, "uwidth");
    layer->agentprog->uheight  = glGetUniformLocation(layer->agentprog->progid, "uheight");
    /* TODO: you know */
    layer->agentprog->uspeed = glGetUniformLocation(layer->agentprog->progid, "uspeed");
    
    /* TODO: move this */
    agents = memalloc(sizeof(Agent) * numagents);
    int x = 1;
    int y = 1;
    for (int i = 0; i < numagents; i++) {
        agents[i].position[0] = x;
        agents[i].position[1] = y;
        agents[i].angle = (i * 0.0001f);
        // printf("agent %f\n", agents[i].angle);
        x++;
        if (x >= 255) { 
            x = 1;
            y+=5;
        }
        if (y >= 255) y = 1;
    }
    
    unsigned int ssbo;
    glGenBuffers(1, &ssbo);
    glBindBuffer(GL_SHADER_STORAGE_BUFFER, ssbo);
    glBufferData(GL_SHADER_STORAGE_BUFFER, sizeof(Agent) * numagents, agents, GL_DYNAMIC_COPY);
    glBindBufferBase(GL_SHADER_STORAGE_BUFFER, 1, ssbo);
    glBindBuffer(GL_SHADER_STORAGE_BUFFER, 0);

    layer->faderprog  = memalloc(sizeof(ShaderProg));
    sprogcomp(layer->faderprog, "../assets/shaders/fader.glsl");
    sproglink(layer->faderprog);
    layer->faderprog->utexture = glGetUniformLocation(layer->faderprog->progid, "utexture");
    layer->faderprog->udelta   = glGetUniformLocation(layer->faderprog->progid, "udelta");
    layer->faderprog->uwidth   = glGetUniformLocation(layer->faderprog->progid, "uwidth");
    layer->faderprog->uheight  = glGetUniformLocation(layer->faderprog->progid, "uheight");

    /* initialize camera */
    layer->camera = memalloc(sizeof(Camera));
    caminit(layer->camera);

    /* initialize things */
    thingsinit();

    /* set camera position */
    camposition(layer->camera, 0.0f, 0.0f, 5.0f);
}

void
layerupdate(Layer *layer, double time)
{
    Thing *thing;

    /* TODO: move this */
    /* dispatch agent compute shader */
    if (moveagents || initagents == 0) {
        glUseProgram(layer->agentprog->progid);
        glUniform1i(layer->agentprog->utexture, 0);
        glUniform1f(layer->agentprog->udelta, time);
        glUniform1i(layer->agentprog->uwidth, 256);
        glUniform1i(layer->agentprog->uheight, 256);
        /* TODO: agent uniforms */
        glUniform1f(layer->agentprog->uspeed, agentspeed);
        glBindImageTexture(0, drawtex, 0, GL_FALSE, 0, GL_WRITE_ONLY, GL_RGBA32F);
        glDispatchCompute(numagents, 20, 1);
        glMemoryBarrier(GL_SHADER_STORAGE_BARRIER_BIT);

        /* dispatch fader compute shader */
        glUseProgram(layer->faderprog->progid);
        glUniform1i(layer->faderprog->utexture, 0);
        glUniform1f(layer->faderprog->udelta, time);
        glUniform1i(layer->faderprog->uwidth, 256);
        glUniform1i(layer->faderprog->uheight, 256);
        glDispatchCompute(256, 256, 1);
        glMemoryBarrier(GL_SHADER_IMAGE_ACCESS_BARRIER_BIT);
        initagents = 1;
    }

    camcontrol(layer->camera, time);

    renderbegin();
    // glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    glUseProgram(layer->shaderprog->progid); // bind
    glUniform1i(layer->shaderprog->utexture, 0);
    glUniform4f(layer->shaderprog->uobjcolor, 1.0f, 0.5f, 0.31f, 1.0f);
    camperspective(layer->camera, glm_rad(45.0), layer->aspect, 0.1f, 100.0f);

    thing = allthings;
    while (thing != NULL) {
        modeltransform(thing->model);
        glUniformMatrix4fv(layer->shaderprog->uviewprojection, 1, GL_FALSE, &(layer->camera->viewprojection)[0][0]);
        glUniformMatrix4fv(layer->shaderprog->utransform,      1, GL_FALSE, &(thing->model->transform)[0][0]);
        modeldraw(thing->model);
        thing = thing->next;
    }
    renderend();
}

void
layerdel(Layer *layer)
{
    memfree(layer->shaderprog);
    memfree(layer->agentprog);
    memfree(layer->faderprog);
    memfree(layer->camera);
    memfree(layer);

    delthings();

    /* TODO: move this */
    memfree(agents);
}

#endif