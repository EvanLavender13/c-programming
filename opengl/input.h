#ifndef INPUT_H_
#define INPUT_H_

#include <cglm/cglm.h>
#include <GLFW/glfw3.h>

#include <mem.h>

struct 
{
    GLFWwindow *winhandle;
} *i;

void
inputinit(GLFWwindow *winhandle)
{
    i = memalloc(sizeof(*i));
    i->winhandle = winhandle;
}

void
inputdel()
{
    memfree(i);
}

int
keypressed(int code)
{  
    int state;

    state = glfwGetKey(i->winhandle, code);
    return  state == GLFW_PRESS || state == GLFW_REPEAT;
}

// /* mouse stuff */
// vec2 prevmouse = GLM_VEC2_ZERO_INIT;
// vec2 currmouse = GLM_VEC2_ZERO_INIT;
// vec2 displayv  = GLM_VEC2_ZERO_INIT;
// int  inwindow = 0;
// int  lmouse  = 0;
// int  rmouse = 0;

// /* keyboard stuff */
// static vec3 movev = GLM_VEC3_ZERO_INIT;

// void
// setcurrmouse(GLFWwindow *w, double x, double y)
// {
//     currmouse[0] = (float) x;
//     currmouse[1] = (float) y;
// }

// void
// setinwindow(GLFWwindow *w, int e)
// {
//     inwindow = e;
// }

// void
// setlrmouse(GLFWwindow *w, int button, int action, int mode)
// {
//     lmouse = (button == GLFW_MOUSE_BUTTON_1 && action == GLFW_PRESS);
//     rmouse = (button == GLFW_MOUSE_BUTTON_2 && action == GLFW_PRESS);
// }

// void
// inputinit(GLFWwindow *w)
// {
//     glfwSetCursorPosCallback(w, setcurrmouse);
//     glfwSetCursorEnterCallback(w, setinwindow);
//     glfwSetMouseButtonCallback(w, setlrmouse);
// }

// void
// input(GLFWwindow *w)
// {
//     bool rx, ry;
//     float dx, dy;

//     displayv[0] = 0.0f;
//     displayv[1] = 0.0f;
//     if (prevmouse[0] > 0 && prevmouse[1] > 0 && inwindow) {
//         dx = currmouse[0] - prevmouse[0];
//         dy = currmouse[1] - prevmouse[1];
//         rx = dx != 0;
//         ry = dy != 0;
//         if (rx) displayv[1] = dx;
//         if (ry) displayv[0] = dy;
//     }
//     prevmouse[0] = currmouse[0];
//     prevmouse[1] = currmouse[1];

//     glm_vec3_zero(movev);
//     if (glfwGetKey(w, GLFW_KEY_W) == GLFW_PRESS)
//         movev[2] = 1.0f;
//     else if (glfwGetKey(w, GLFW_KEY_S) == GLFW_PRESS)
//         movev[2] = -1.0f;

//     if (glfwGetKey(w, GLFW_KEY_A) == GLFW_PRESS)
//         movev[0] = 1.0f;
//     else if (glfwGetKey(w, GLFW_KEY_D) == GLFW_PRESS)
//         movev[0] = -1.0f;

//     if (glfwGetKey(w, GLFW_KEY_X) == GLFW_PRESS)
//         movev[1] = 1.0f;
//     else if (glfwGetKey(w, GLFW_KEY_SPACE) == GLFW_PRESS)
//         movev[1] = -1.0f;
// }

// vec3 camposition  = {0.0f, 0.0f, 5.0f};
// vec3 camdirection = GLM_VEC3_ZERO_INIT;
// vec3 camright     = GLM_VEC3_ZERO_INIT;
// vec3 camup        = GLM_VEC3_ZERO_INIT;
// vec3 camcenter    = GLM_VEC3_ZERO_INIT;
// float camfov;

// float hangle = 3.14f;
// float vangle = 0.0f;
// float initfov = 45.0f;

// float speed = 3.0f; /* 3 units per second */
// float mousespeed = 0.05f;

// double xpos, ypos;

// void
// input(GLFWwindow *w, double delta)
// {
//     int width, height;

//     glfwGetWindowSize(w, &width, &height);

//     glfwGetCursorPos(w, &xpos, &ypos);
//     glfwSetCursorPos(w, width / 2, height / 2);

//     hangle += mousespeed * delta * (width / 2 - xpos);
//     vangle += mousespeed * delta * (height / 2 - ypos);

//     camdirection[0] = cos(vangle) * sin(hangle);
//     camdirection[1] = sin(vangle);
//     camdirection[2] = cos(vangle) * cos(hangle);

//     camright[0] = sin(hangle - 3.14f / 2.0f);
//     camright[1] = 0.0f;
//     camright[2] = cos(hangle - 3.14f / 2.0f);

//     glm_cross(camright, camdirection, camup);

//     /* forward */
//     if (glfwGetKey(w, GLFW_KEY_W) == GLFW_PRESS) {
//         glm_vec3_scale(camdirection, delta * speed, camdirection);
//         glm_vec3_add(camposition, camdirection, camposition);

//     }
//     /* back */
//     if (glfwGetKey(w, GLFW_KEY_S) == GLFW_PRESS) {
//         glm_vec3_scale(camdirection, delta * speed, camdirection);
//         glm_vec3_sub(camposition, camdirection, camposition);
//     }
//     /* left */
//     if (glfwGetKey(w, GLFW_KEY_A) == GLFW_PRESS) {
//         glm_vec3_scale(camright, delta * speed, camright);
//         glm_vec3_sub(camposition, camright, camposition);
//     }
//     /* right */
//     if (glfwGetKey(w, GLFW_KEY_D) == GLFW_PRESS) {
//         glm_vec3_scale(camright, delta * speed, camright);
//         glm_vec3_add(camposition, camright, camposition);
//     }

//     glm_vec3_add(camposition, camdirection, camcenter);
// }

#endif