#include <stdio.h>

#define GLEW_STATIC
#include <GL/glew.h>

#include <app.h>
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

    instance->layer = memalloc(sizeof(Layer));
    layerinit(instance->winhandle, instance->layer);

    apprun();
    appdel();
    error();

    printf("References remaining: %d\n", nrefs);
    return 0;
}