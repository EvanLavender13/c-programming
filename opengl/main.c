#include <stdio.h>

#define GLEW_STATIC
#include <GL/glew.h>

#include <app.h>
#include <guilayer.h>
#include <layer.h>

void
error()
{
    GLenum err;
    for (;;) {
        err = glGetError();
        if (err == GL_NO_ERROR) break;
        printf("ERROR: %d\n", err);
    }
}

int
main()
{
    appinit("Super Window");

    /* TODO: maybe do this somewhere else? */
    instance->layer = memalloc(sizeof(Layer));
    layerinit(instance->winhandle, instance->layer);

    instance->gui = memalloc(sizeof(Gui));
    guiinit(instance->winhandle, instance->gui);

    apprun();
    appdel();
    error();

    printf("References remaining: %d\n", nrefs);
    return 0;
}