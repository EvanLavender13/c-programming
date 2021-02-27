#ifndef MESH_H_
#define MESH_H_

#include <GL/glew.h>

typedef struct Mesh Mesh;
struct Mesh
{
    unsigned int vao;
    unsigned int vbo; // vertex buffer
    unsigned int ibo; // index buffer
    unsigned int cbo; // color buffer
    int nvertices;
};

typedef struct MeshDef MeshDef;
struct MeshDef
{
    float  *vertices;
    int     nvertices;
    int     vsize;

    int    *indices; 
    int     nindices;
    int     isize;

    float  *colors;
    int     ncolors;
    int     csize;
};

void
meshinit(Mesh *mesh, MeshDef *def)
{
    mesh->nvertices = def->nindices;
    glGenVertexArrays(1, &(mesh->vao));
    glBindVertexArray(mesh->vao);

    // generate vertex buffer
    glGenBuffers(1, &(mesh->vbo));
    glBindBuffer(GL_ARRAY_BUFFER, mesh->vbo);
    glBufferData(GL_ARRAY_BUFFER, def->vsize, def->vertices, GL_STATIC_DRAW);
    // position in shader (index 0)
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);

    // generate index buffer
    glGenBuffers(1, &(mesh->ibo));
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mesh->ibo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, def->isize, def->indices, GL_STATIC_DRAW);

    // generate color buffer
    glGenBuffers(1, &(mesh->cbo));
    glBindBuffer(GL_ARRAY_BUFFER, mesh->cbo);
    glBufferData(GL_ARRAY_BUFFER, def->csize, def->colors, GL_STATIC_DRAW);
    // color in shader (index 1)
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, 0);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}

void
delmesh(Mesh *mesh)
{
    glDisableVertexAttribArray(0);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glDeleteBuffers(1, &(mesh->vbo));
    glDeleteBuffers(1, &(mesh->ibo));

    glBindVertexArray(0);
    glDeleteVertexArrays(1, &(mesh->vao));
    memfree(mesh);
}

#endif