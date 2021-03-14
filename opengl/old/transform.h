#ifndef TRANSFORM_H_
#define TRANSFORM_H_

#include <cglm/cglm.h>

// static mat4 tprojection  = GLM_MAT4_IDENTITY_INIT;
// static mat4 tview        = GLM_MAT4_IDENTITY_INIT;
// static mat4 tmodel       = GLM_MAT4_IDENTITY_INIT;
// static mat4 tmvp         = GLM_MAT4_IDENTITY_INIT;

// void
// updateproj(float fov, float aspect, float near, float far)
// {
//     glm_mat4_identity(tprojection);
//     glm_perspective(fov, aspect, near, far, tprojection);
// }

// void
// updateview(Camera *cam)
// {
//     float x, y, z;

//     x = glm_rad(cam->rot[0]);
//     y = glm_rad(cam->rot[1]);
//     z = glm_rad(cam->rot[2]);

//     glm_mat4_identity(tview);
//     glm_rotate_x(tview, x, tview);
//     glm_rotate_y(tview, y, tview);
//     glm_rotate_z(tview, z, tview);
//     glm_translate(tview, cam->pos);
// }

// void
// updatemodel(Model *m)
// {
//     float x, y, z;

//     x = glm_rad(m->rot[0]);
//     y = glm_rad(m->rot[1]);
//     z = glm_rad(m->rot[2]);

//     glm_mat4_identity(tmodel);
//     glm_translate(tmodel, m->pos);
//     glm_rotate_x(tmodel, -x, tmodel);
//     glm_rotate_y(tmodel, -y, tmodel);
//     glm_rotate_z(tmodel, -z, tmodel);
//     glm_scale_uni(tmodel, m->scale);
// }

// void
// updatemvp()
// {
//     glm_mat4_identity(tmvp);
//     glm_mat4_mul(tprojection, tview, tmvp);
//     glm_mat4_mul(tmvp, tmodel, tmvp);
// }

// void 
// updateworld(vec3 off, vec3 rot, float scale)
// {
//     float x, y, z;

//     x = glm_rad(rot[0]);
//     y = glm_rad(rot[1]);
//     z = glm_rad(rot[2]);

//     glm_mat4_identity(world);
//     glm_translate(world, off);
//     glm_rotate_x(world, x, world);
//     glm_rotate_y(world, y, world);
//     glm_rotate_z(world, z, world);
//     glm_scale_uni(world, scale);
// }

// void
// updatemodelview(Model *mod)
// {
//     float x, y, z;

//     x = glm_rad(mod->rot[0]);
//     y = glm_rad(mod->rot[1]);
//     z = glm_rad(mod->rot[2]);

//     glm_mat4_identity(modelview);
//     glm_translate(modelview, mod->pos);
//     glm_rotate_x(modelview, -x, modelview);
//     glm_rotate_y(modelview, -y, modelview);
//     glm_rotate_z(modelview, -z, modelview);
//     glm_scale_uni(modelview, mod->scale);

//     glm_mat4_mul(view, modelview, modelview);
// }

#endif
