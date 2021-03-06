#ifndef MESH_H_
#define MESH_H_

#include <GL/glew.h>

#include <mem.h>

typedef struct Mesh Mesh;
struct Mesh
{
    unsigned int vertarr; /* vao */

    unsigned int vertbuf;
    unsigned int colrbuf;

    int vertsize;
    int colrsize;
};

void
meshinit(Mesh *m, float *vert, float *colr)
{
    m->vertsize = sizeof(float) * (int) *vert++;
    m->colrsize = sizeof(float) * (int) *colr++;

    glGenVertexArrays(1, &(m->vertarr));
    glBindVertexArray(m->vertarr);

    glGenBuffers(1, &(m->vertbuf));
    glBindBuffer(GL_ARRAY_BUFFER, m->vertbuf);
    glBufferData(GL_ARRAY_BUFFER, m->vertsize, vert, GL_STATIC_DRAW);

    glGenBuffers(1, &(m->colrbuf));
    glBindBuffer(GL_ARRAY_BUFFER, m->colrbuf);
    glBufferData(GL_ARRAY_BUFFER, m->colrsize, colr, GL_STATIC_DRAW);
}

void
drawmesh(Mesh *m)
{
    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);

    glBindBuffer(GL_ARRAY_BUFFER, m->vertbuf);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);

    glBindBuffer(GL_ARRAY_BUFFER, m->colrbuf);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, 0);

    glDrawArrays(GL_TRIANGLES, 0, 36); // TODO: something

    glDisableVertexAttribArray(0);
    glDisableVertexAttribArray(1);
}

void
delmesh(Mesh *m)
{
    glDisableVertexAttribArray(0);
    glDisableVertexAttribArray(1);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glDeleteBuffers(1, &(m->vertbuf));
    glDeleteBuffers(1, &(m->colrbuf));

    glBindVertexArray(0);
    glDeleteVertexArrays(1, &(m->vertarr));
    memfree(m);
}

#endif