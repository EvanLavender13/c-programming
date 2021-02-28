#ifndef MOUSE_H_
#define MOUSE_H_

#include <cglm/cglm.h>
#include <GLFW/glfw3.h>

// mouse positions
static vec2 prevmouse = { -1.0f, -1.0f };
static vec2 currmouse = GLM_VEC2_ZERO_INIT;
static vec2 display   = GLM_VEC2_ZERO_INIT;

static bool inwindow = false;
static bool lmouse = false;
static bool rmouse = false;

void
setcurrmouse(GLFWwindow *w, double x, double y)
{
    currmouse[0] = (float) x;
    currmouse[1] = (float) y;
}

void
setinwindow(GLFWwindow *w, int e)
{
    inwindow = (e == 1) ? true : false;
}

void
setlrmouse(GLFWwindow *w, int button, int action, int mode)
{
    lmouse = (button == GLFW_MOUSE_BUTTON_1 && action == GLFW_PRESS);
    rmouse = (button == GLFW_MOUSE_BUTTON_2 && action == GLFW_PRESS);
}

void
mouseinit(GLFWwindow *w)
{
    glfwSetCursorPosCallback(w, setcurrmouse);
    glfwSetCursorEnterCallback(w, setinwindow);
    glfwSetMouseButtonCallback(w, setlrmouse);
}

void
inputmouse()
{
    bool rx, ry;
    float dx, dy;

    display[0] = 0.0f;
    display[1] = 0.0f;
    if (prevmouse[0] > 0 && prevmouse[1] > 0 && inwindow) {
        dx = currmouse[0] - prevmouse[0];
        dy = currmouse[1] - prevmouse[1];
        rx = dx != 0;
        ry = dy != 0;
        if (rx) display[1] = dx;
        if (ry) display[0] = dy;
    }
    prevmouse[0] = currmouse[0];
    prevmouse[1] = currmouse[1];
}

#endif