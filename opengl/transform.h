#ifndef TRANSFORM_H_
#define TRANSFORM_H_

#include <cglm/cglm.h>

static mat4 projection  = GLM_MAT4_IDENTITY_INIT;
static mat4 world       = GLM_MAT4_IDENTITY_INIT;

void
updateproj(float fov, int width, int height, float znear, float zfar)
{
    float aspect;

    aspect = (float) width / height;
    glm_mat4_identity(projection);
    glm_perspective(fov, aspect, znear, zfar, projection);
}

// TODO: should this happen in shader?
void updateworld(vec3 off, vec3 rot, float scale)
{
    float x, y, z;

    x = glm_rad(rot[0]);
    y = glm_rad(rot[1]);
    z = glm_rad(rot[2]);

    glm_mat4_identity(world);
    glm_translate(world, off);
    glm_rotate_x(world, x, world);
    glm_rotate_y(world, y, world);
    glm_rotate_z(world, z, world);
    glm_scale_uni(world, scale);
}

#endif
