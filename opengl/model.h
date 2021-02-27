#ifndef MODEL_H_
#define MODEL_H_

#include <cglm/cglm.h>

#include <mesh.h>

typedef struct Model Model;
struct Model
{
    Mesh   *mesh;
    vec3    pos;
    vec3    rot;
    float   scale;
};

void
modelinit(Model *mod, Mesh *mesh)
{
    mod->mesh = mesh;
    glm_vec3_zero(mod->pos);
    glm_vec3_zero(mod->rot);
    mod->scale = 1.0f;
}

void
delmodel(Model *mod)
{
    delmesh(mod->mesh);
    memfree(mod);
}

#endif