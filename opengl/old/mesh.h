#ifndef MESH_H_
#define MESH_H_

#include <errno.h>
#include <stdio.h>

#include <cglm/cglm.h>
#include <fast_obj.h>
#include <GL/glew.h>

typedef struct Mesh Mesh;
struct Mesh
{
    unsigned int vao;
    unsigned int vbo; // vertex buffer
    unsigned int ibo; // index buffer
    unsigned int tbo; // color/texture buffer
    unsigned int nbo; // normals buffer
    int nvertices;
    int texid;

    // TODO: maybe have this in model?
    vec3 color;
};

// TODO: this structure is already annoying
typedef struct MeshDef MeshDef;
struct MeshDef
{
    float  *vertices;
    int     nvertices;
    int     vsize;

    int    *indices; 
    int     nindices;
    int     isize;

    // TODO: maybe make this an option?
    // float  *colors;
    // int     ncolors;
    // int     csize;
    int     texid;
    float  *texcoords;
    int     ntexcoords;
    int     tsize;

    float  *normals;
    int     nnormals;
    int     nsize;
};

void
meshinit(Mesh *mesh, MeshDef *def)
{
    glm_vec3_one(mesh->color);
    mesh->color[0] = 0.0f;
    mesh->nvertices = def->nvertices;
    mesh->texid = def->texid;
    glGenVertexArrays(1, &(mesh->vao));
    glBindVertexArray(mesh->vao);
    
    // generate vertex buffer
    glGenBuffers(1, &(mesh->vbo));
    glBindBuffer(GL_ARRAY_BUFFER, mesh->vbo);
    glBufferData(GL_ARRAY_BUFFER, def->vsize, def->vertices, GL_STATIC_DRAW);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);

    // generate index buffer
    glGenBuffers(1, &(mesh->ibo));
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mesh->ibo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, def->isize, def->indices, GL_STATIC_DRAW);

    // generate texture buffer
    glGenBuffers(1, &(mesh->tbo));
    glBindBuffer(GL_ARRAY_BUFFER, mesh->tbo);
    glBufferData(GL_ARRAY_BUFFER, def->tsize, def->texcoords, GL_STATIC_DRAW);
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, 0);

    // generate normals buffer
    glGenBuffers(1, &(mesh->nbo));
    glBindBuffer(GL_ARRAY_BUFFER, mesh->nbo);
    glBufferData(GL_ARRAY_BUFFER, def->nsize, def->normals, GL_STATIC_DRAW);
    glEnableVertexAttribArray(2);
    glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 0, 0);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}

void
meshinitobj(Mesh *mesh, char *fp)
{
    // TODO: this a good size?
    char line[1024];
    FILE *f;
    MeshDef def;

    f = fopen(fp, "rb");
    if (f == NULL) {
        printf("unable to open file: %s, errno: %d\n", fp, errno);
        return;
    }

    while (fgets(line, sizeof(line), f)) {
        printf("%s", line);
    }

    // fastObjMesh *fmesh;

    // fmesh = fast_obj_read(fp);
    // // get vertices/positions
    // def.vertices = fmesh->positions;
    // def.nvertices = fmesh->position_count * 3;
    // def.vsize = sizeof(float) * def.nvertices;

    // // get indices
    // n = fmesh->face_count * 3;
    // indices = memalloc(sizeof(int) * n);
    // for (i = 0; i < fmesh->face_count; i++) {
    //     indices[i * 3]     = (fmesh->indices + i)->n;
    //     indices[i * 3 + 1] = (fmesh->indices + i)->p;
    //     indices[i * 3 + 2] = (fmesh->indices + i)->t;
    // }

    // def.indices = indices;
    // def.nindices = n / sizeof(int);
    // def.isize = sizeof(int) * def.nindices;

    // // get texture coords
    // def.texcoords = fmesh->texcoords;
    // def.ntexcoords = fmesh->texcoord_count * 2;
    // def.tsize = sizeof(float) * def.ntexcoords;

    // meshinit(mesh, &def);

    // memfree(indices);
    // fast_obj_destroy(fmesh);
}

void
delmesh(Mesh *mesh)
{
    glDisableVertexAttribArray(0);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glDeleteBuffers(1, &(mesh->vbo));
    glDeleteBuffers(1, &(mesh->ibo));
    glDeleteBuffers(1, &(mesh->tbo));
    glDeleteBuffers(1, &(mesh->nbo));

    glBindVertexArray(0);
    glDeleteVertexArrays(1, &(mesh->vao));
    memfree(mesh);
}



#endif