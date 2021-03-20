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
};

void
layerinit(GLFWwindow *winhandle, Layer *layer)
{
    int width, height;

    glfwGetWindowSize(winhandle, &width, &height);
    layer->aspect = (float) width / (float) height;

    /* initialize shader program(s) */
    layer->shaderprog = memalloc(sizeof(ShaderProg));
    sproginit(layer->shaderprog, "../assets/shaders/vert.glsl", "../assets/shaders/frag.glsl");
    sproglink(layer->shaderprog);

    /* TODO: add to shader prog or something? */
    layer->shaderprog->uviewprojection = glGetUniformLocation(layer->shaderprog->progid, "uviewprojection");
    layer->shaderprog->utransform      = glGetUniformLocation(layer->shaderprog->progid, "utransform");
    layer->shaderprog->uobjcolor       = glGetUniformLocation(layer->shaderprog->progid, "uobjcolor");

    /* initialize camera */
    layer->camera = memalloc(sizeof(Camera));
    caminit(layer->camera);

    /* initialize things */
    thingsinit();

    /* set camera position */
    camposition(layer->camera, 0.0f, 0.0f, 5.0f);

    renderviewport(0, 0, width, height);
}

void
layerupdate(Layer *layer, double time)
{
    Thing *thing;

    camcontrol(layer->camera, time);

    renderbegin();
    glUseProgram(layer->shaderprog->progid); // bind
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
    memfree(layer->camera);
    memfree(layer);

    delthings();
}

#endif