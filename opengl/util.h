#ifndef UTIL_H_
#define UTIL_H_

#include <stdio.h>

#include <GLFW/glfw3.h>

#include <mem.h>

#define UNUSED(x) (void)(x)

int
fsize(FILE *f)
{
    int sz;

    fseek(f, 0l, SEEK_END);
    sz = ftell(f);
    fseek(f, 0, SEEK_SET);
    return sz;
}

struct
{
    double currtime;
    double lasttime;
    double time;
} *delta;


void
deltainit()
{
    delta = memalloc(sizeof(*delta));
}

void
deltaupdate()
{
    delta->lasttime = delta->currtime;
    delta->currtime = glfwGetTime();
    delta->time = delta->currtime - delta->lasttime;
}

void
deltadel()
{
    memfree(delta);
}



struct
{
    int    framecount;
    double currtime;
    double lasttime;
} *fps;

//static FPS *fps = NULL;

void
fpsinit()
{
    fps = memalloc(sizeof(*fps));
    fps->lasttime = glfwGetTime();
    fps->currtime = glfwGetTime();
    fps->framecount = 0;
}

void
fpsdel()
{
    memfree(fps);
}

void
fpsupdate()
{
    fps->currtime = glfwGetTime();
    fps->framecount++;
    if (fps->currtime - fps->lasttime >= 1.0) {
        printf("%f ms/frame %d fps\n", 1000.0 / fps->framecount, fps->framecount);
        fps->framecount = 0;
        fps->lasttime++;
    }
}

#endif