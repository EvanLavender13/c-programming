#ifndef MODEL_H_
#define MODEL_H_

#include <cglm/cglm.h>

#include <mesh.h>

typedef struct Model Model;
struct Model
{
    Mesh    *mesh;
    vec3     pos;
    vec3     rot;
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
drawmodel(Model *m)
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
    mod->pos[0] = x;
    mod->pos[1] = y;
    mod->pos[2] = z;  
}

void
setrotmodel(Model *mod, float x, float y, float z)
{
    mod->rot[0] = x;
    mod->rot[1] = y;
    mod->rot[2] = z;
}

#endif