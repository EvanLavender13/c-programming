#ifndef CAMERA_H_
#define CAMERA_H_

#include <cglm/cglm.h>

typedef struct Camera Camera;
struct Camera
{
    vec3 pos;
    vec3 rot;
};

void
caminit(Camera *cam)
{
    glm_vec3_zero(cam->pos);
    glm_vec3_zero(cam->rot);
}

void
poscam(Camera *cam, float x, float y, float z)
{
    cam->pos[0] = x;
    cam->pos[1] = y;
    cam->pos[2] = z;
}

void
movecam(Camera *cam, float offx, float offy, float offz)
{
    if (offz != 0) {
        cam->pos[0] += (float) sin(glm_rad(cam->rot[1])) * -1.0f * offz;
        cam->pos[2] += (float) cos(glm_rad(cam->rot[1])) * offz;
    }
    if (offx != 0) {
        cam->pos[0] += (float) sin(glm_rad(cam->rot[1] - 90)) * -1.0f * offx;
        cam->pos[2] += (float) cos(glm_rad(cam->rot[1] - 90)) * offx; 
    }
    cam->pos[1] += offy;
}

// void
// rotcam(Camera *cam, float x, float y, float z)
// {
//     cam->rot[0] = x;
//     cam->rot[1] = y;
//     cam->rot[2] = z;
// }

void
rotcam(Camera *cam, float offx, float offy, float offz)
{
    cam->rot[0] += offx;
    cam->rot[1] += offy;
    cam->rot[2] += offz;
}

#endif
