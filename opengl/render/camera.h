#ifndef CAMERA_H_
#define CAMERA_H_

#include <cglm/cglm.h>
#include <GLFW/glfw3.h>

#include <input.h>

/* orthographic for now? */
typedef struct Camera Camera;
struct Camera
{
    mat4  projection;
    mat4  view;
    mat4  viewprojection;
    vec3  position;
    // float rotation;
    vec3  rotation;
    float translationspeed;
    float rotationspeed;
};

vec3 X_AXIS = { 1.0f, 0.0f, 0.0f };
vec3 Y_AXIS = { 0.0f, 1.0f, 0.0f };
vec3 Z_AXIS = { 0.0f, 0.0f, 1.0f };

void
caminit(Camera *cam)
{
    glm_mat4_zero(cam->projection);
    glm_mat4_zero(cam->view);
    glm_mat4_zero(cam->viewprojection);
    glm_vec3_zero(cam->position);
    // cam->rotation = 0.0f;
    glm_vec3_zero(cam->rotation);
    cam->translationspeed = 5.0f;
    cam->rotationspeed = 10.0f;
}

void
camortho(Camera *cam, float left, float right, float bottom, float top)
{
    glm_mat4_identity(cam->projection);
    glm_ortho(left, right, bottom, top, -1.0f, 1.0f, cam->projection);
    // glm_perspective(l, r, b, t, cam->projection);
    // glm_mat4_mul(cam->projection, cam->view, cam->viewprojection);
}

void
camperspective(Camera *cam, float fov, float aspect, float near, float far)
{
    glm_mat4_identity(cam->projection);
    glm_perspective(fov, aspect, near, far, cam->projection);
    // glm_mat4_mul(cam->projection, cam->view, cam->viewprojection);
}

void
camcalc(Camera *cam)
{
    // mat4 transform = GLM_MAT4_IDENTITY_INIT;
    // mat4 translate = GLM_MAT4_IDENTITY_INIT;
    // mat4 rotate    = GLM_MAT4_IDENTITY_INIT;
    glm_mat4_identity(cam->view);
    // glm_translate(cam->view, cam->position);
    // glm_rotate(cam->view, glm_rad(cam->rotation[0]), X_AXIS);
    // glm_rotate(cam->view, glm_rad(cam->rotation[1]), Y_AXIS);
    
    /* TODO: learn more about this, lol */
    // glm_rotate(rotate, glm_rad(cam->rotation), Z_AXIS);
    glm_rotate_x(cam->view, glm_rad(cam->rotation[0]), cam->view);
    glm_rotate_y(cam->view, glm_rad(cam->rotation[1]), cam->view);
    // glm_rotate_z(rotate, glm_rad(-cam->rotation[2]), rotate);
    // glm_translate(translate, cam->position);
    glm_translate_x(cam->view, -cam->position[0]);
    glm_translate_y(cam->view, -cam->position[1]);
    glm_translate_z(cam->view, -cam->position[2]);
    // glm_mat4_mul(translate, rotate, cam->view);
    // glm_inv_tr(cam->view);
    glm_mat4_mul(cam->projection, cam->view, cam->viewprojection);
}

void
camposition(Camera *cam, float x, float y, float z)
{
    cam->position[0] = x;
    cam->position[1] = y;
    cam->position[2] = z;
    camcalc(cam);
}

void
cammove(Camera *cam, float offx, float offy, float offz)
{
    if (offz != 0) {
        cam->position[0] += (float) sin(glm_rad(cam->rotation[1])) * -1.0f * offz;
        cam->position[2] += (float) cos(glm_rad(cam->rotation[1])) * offz;
    }
    if (offx != 0) {
        cam->position[0] += (float) sin(glm_rad(cam->rotation[1] - 90.0f)) * -1.0f * offx;
        cam->position[2] += (float) cos(glm_rad(cam->rotation[1] - 90.0f)) * offx; 
    }
    cam->position[1] += offy;
}

void
camrotate(Camera *cam, float offx, float offy, float offz)
{
    cam->rotation[0] += offx;
    cam->rotation[1] += offy;
    cam->rotation[2] += offz;
}

void
camcontrol(Camera *cam, double time)
{
    float x = 0, y = 0, z = 0;
    float dx, dy;

    /* handle keys */
    if (keypressed(GLFW_KEY_A))     x = -1.0f;
    if (keypressed(GLFW_KEY_D))     x =  1.0f;
    if (keypressed(GLFW_KEY_W))     z = -1.0f;
    if (keypressed(GLFW_KEY_S))     z =  1.0f;
    if (keypressed(GLFW_KEY_X))     y = -1.0f;
    if (keypressed(GLFW_KEY_SPACE)) y =  1.0f;
    x *= cam->translationspeed * time;
    y *= cam->translationspeed * time;
    z *= cam->translationspeed * time;
    cammove(cam, x, y, z);

    /* handle mouse */
    if (input->mouseprev[0] > 0.0f && input->mouseprev[1] > 0.0f && input->inwindow) {
        dx = input->mousecurr[0] - input->mouseprev[0];
        dy = input->mousecurr[1] - input->mouseprev[1];
    }
    input->mouseprev[0] = input->mousecurr[0];
    input->mouseprev[1] = input->mousecurr[1];
    if (input->mouserpress && input->inwindow) {
        dx *= cam->rotationspeed * time;
        dy *= cam->rotationspeed * time;
        camrotate(cam, dy, dx, 0.0f);
    }

    camcalc(cam);

    // if (keypressed(GLFW_KEY_A)) {
    //     cam->position[0] -= cos(glm_rad(cam->rotation)) * cam->translationspeed * time;
    //     cam->position[1] -= sin(glm_rad(cam->rotation)) * cam->translationspeed * time;
    // }
    // if (keypressed(GLFW_KEY_D)) {
    //     cam->position[0] += cos(glm_rad(cam->rotation)) * cam->translationspeed * time;
    //     cam->position[1] += sin(glm_rad(cam->rotation)) * cam->translationspeed * time;
    // }
    // if (keypressed(GLFW_KEY_W)) {
    //     cam->position[0] += -sin(glm_rad(cam->rotation)) * cam->translationspeed * time;
    //     cam->position[2] -= cos(glm_rad(cam->rotation)) * cam->translationspeed * time;
    // }
    // if (keypressed(GLFW_KEY_S)) {
    //     cam->position[0] -= -sin(glm_rad(cam->rotation)) * cam->translationspeed * time;
    //     cam->position[2] += cos(glm_rad(cam->rotation)) * cam->translationspeed * time;
    // }

    // if (cam->rotation) {
        // if (keypressed(GLFW_KEY_Q))
        //     cam->rotation += cam->rotationspeed * time;
        // if (keypressed(GLFW_KEY_E))
        //     cam->rotation -= cam->rotationspeed * time;
        // if (cam->rotation > 180.0f)
        //     cam->rotation -= 360.0f;
        // else if (cam->rotation <= -180.0f)
        //     cam->rotation += 360.0f;
    // }
}

// struct Camera
// {
//     vec3 pos;
//     vec3 rot;
// };

// void
// caminit(Camera *cam)
// {
//     glm_vec3_zero(cam->pos);
//     glm_vec3_zero(cam->rot);
// }

// void
// poscam(Camera *cam, float x, float y, float z)
// {
//     cam->pos[0] = x;
//     cam->pos[1] = y;
//     cam->pos[2] = z;
// }

// void
// movecam(Camera *cam, float offx, float offy, float offz)
// {
//     if (offz != 0) {
//         cam->pos[0] += (float) sin(glm_rad(cam->rot[1])) * -1.0f * offz;
//         cam->pos[2] += (float) cos(glm_rad(cam->rot[1])) * offz;
//     }
//     if (offx != 0) {
//         cam->pos[0] += (float) sin(glm_rad(cam->rot[1] - 90)) * -1.0f * offx;
//         cam->pos[2] += (float) cos(glm_rad(cam->rot[1] - 90)) * offx; 
//     }
//     cam->pos[1] += offy;
// }

// void
// rotcam(Camera *cam, float offx, float offy, float offz)
// {
//     cam->rot[0] += offx;
//     cam->rot[1] += offy;
//     cam->rot[2] += offz;
// }

#endif
