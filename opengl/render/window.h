#ifndef WINDOW_H_
#define WINDOW_H_

#include <GLFW/glfw3.h>

#include <context.h>

void
errcallback(int err, const char *desc)
{
    printf("GLFW Error (%d): %s\n", err, desc);
}

void
winvsync(int v)
{
    glfwSwapInterval(v);
}

GLFWwindow *
wininit(int width, int height, char *name)
{
    int success;
    GLFWwindow *winhandle;

    success = glfwInit();
    if (success == 0) return NULL;
    glfwSetErrorCallback(errcallback);

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);
    winhandle = glfwCreateWindow(width, height, name, NULL, NULL);

    ctxinit(winhandle);
    winvsync(1);

    return winhandle;
}

void
winupdate(GLFWwindow *winhandle)
{
    glfwPollEvents();
    ctxswap(winhandle);
}

void
windel(GLFWwindow *winhandle)
{
    glfwDestroyWindow(winhandle);
    glfwTerminate();
}

#endif