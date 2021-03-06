#ifndef KEYBOARD_H_
#define KEYBOARD_H_

#include <cglm/cglm.h>
#include <GLFW/glfw3.h>

// movement vector
static vec3 move = GLM_VEC3_ZERO_INIT;

void
inputkb(GLFWwindow *w)
{
    glm_vec3_zero(move);
    if (glfwGetKey(w, GLFW_KEY_W) == GLFW_PRESS)
        move[2] = 1.0f;
    else if (glfwGetKey(w, GLFW_KEY_S) == GLFW_PRESS)
        move[2] = -1.0f;

    if (glfwGetKey(w, GLFW_KEY_A) == GLFW_PRESS)
        move[0] = 1.0f;
    else if (glfwGetKey(w, GLFW_KEY_D) == GLFW_PRESS)
        move[0] = -1.0f;

    if (glfwGetKey(w, GLFW_KEY_Z) == GLFW_PRESS)
        move[1] = 1.0f;
    else if (glfwGetKey(w, GLFW_KEY_X) == GLFW_PRESS)
        move[1] = -1.0f;
}

#endif