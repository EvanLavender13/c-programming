#ifndef CONTEXT_H_
#define CONTEXT_H_

#include <GL/glew.h>
#include <GLFW/glfw3.h>

void
ctxinit(GLFWwindow *winhandle)
{
    glfwMakeContextCurrent(winhandle);
    glewExperimental = GL_TRUE; // TODO: what is this?
    glewInit();

    printf("OpenGL Info:\n");
    printf("  Vendor: %s\n", glGetString(GL_VENDOR));
    printf("  Renderer: %s\n", glGetString(GL_RENDERER));
    printf("  Version: %s\n", glGetString(GL_VERSION));
}

void
ctxswap(GLFWwindow *winhandle)
{
    glfwSwapBuffers(winhandle);
}

#endif