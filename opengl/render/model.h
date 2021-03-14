#ifndef MODEL_H_
#define MODEL_H_

#include <cglm/cglm.h>

#include <mesh.h>

typedef struct Model Model;
struct Model
{
    Mesh    *mesh;
    vec3     position;
    vec3     rotation;
    float    scale;

    mat4     transform;
};

void
modelinit(Model *mod, Mesh *mesh)
{
    mod->mesh = mesh;
    glm_vec3_zero(mod->position);
    glm_vec3_zero(mod->rotation);
    mod->scale = 1.0f;

    glm_mat4_zero(mod->transform);
}

void
modeltransform(Model *mod)
{
    glm_mat4_identity(mod->transform);
    glm_translate(mod->transform, mod->position);
    // glm_rotate_x(mod->transform, -mod->rotation[0], mod->transform);
    // glm_rotate_y(mod->transform, -mod->rotation[1], mod->transform);
    // glm_rotate_z(mod->transform, -mod->rotation[2], mod->transform);
    glm_scale_uni(mod->transform, mod->scale);
}

void
modeldraw(Model *m)
{
    glBindVertexArray(m->mesh->vertarr);
    drawmesh(m->mesh);
}

void
delmodel(Model *mod)
{
    memfree(mod);
}

void
setposmodel(Model *mod, float x, float y, float z)
{
    mod->position[0] = x;
    mod->position[1] = y;
    mod->position[2] = z;  
}

void
setrotmodel(Model *mod, float x, float y, float z)
{
    mod->rotation[0] = x;
    mod->rotation[1] = y;
    mod->rotation[2] = z;
}

#endif