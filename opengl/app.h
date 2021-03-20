#ifndef APP_H_
#define APP_H_

#include <GLFW/glfw3.h>

#include <input.h>
#include <layer.h>
#include <mem.h>
#include <render.h>
#include <util.h>
#include <window.h>

typedef struct App App;
struct App
{
    char *name;
    int   minimized;
    int   running;
    // float lastframetime;
    GLFWwindow *winhandle;
    /* TODO: layers? */
    Layer *layer;
};

static App *instance = NULL;

void
appclose()
{
    printf("Closing \"%s\"\n", instance->name);
    instance->running = 0;
}

void
appinit(char *name)
{
    printf("Initializing \"%s\"\n", name);
    instance = memalloc(sizeof(App));
    instance->winhandle = wininit(1000, 800, name);
    instance->name = name;
    instance->minimized = 0;
    instance->running   = 1;
    
    glfwSetWindowCloseCallback(instance->winhandle, appclose);
    
    renderinit();

    /* TODO: gui? */

    inputinit(instance->winhandle);
    deltainit();
    fpsinit();
}

/* TODO: layers */

void
apprun()
{
    while (instance->running) {
        deltaupdate();

        if (instance->minimized == 0) {
            layerupdate(instance->layer, delta->time);

            /* TODO: gui? */
        }

        winupdate(instance->winhandle);

        fpsupdate();
    }
}

void
appdel()
{
    windel(instance->winhandle);

    layerdel(instance->layer);
    memfree(instance);
    /* TODO: render shutdown? */

    inputdel();
    deltadel();
    fpsdel();
}

#endif