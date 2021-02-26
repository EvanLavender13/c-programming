#ifndef MESH_H_
#define MESH_H_

#include <GL/glew.h>

typedef struct Mesh Mesh;
struct Mesh
{
    unsigned int vao;
    unsigned int vbo; // vertex buffer
    unsigned int ibo; // index buffer
    int nvertices;
};

void
meshinit(Mesh *mesh, float *v, int nv, int *i, int ni)
{
    mesh->nvertices = ni;
    glGenVertexArrays(1, &(mesh->vao));
    glBindVertexArray(mesh->vao);

    glGenBuffers(1, &(mesh->vbo));
    glBindBuffer(GL_ARRAY_BUFFER, mesh->vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(v) * nv, v, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);

    glGenBuffers(1, &(mesh->ibo));
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mesh->ibo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(i) * ni, i, GL_STATIC_DRAW);

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