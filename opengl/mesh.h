#ifndef MESH_H_
#define MESH_H_

#include <errno.h>
#include <stdio.h>

#include <GL/glew.h>

#include <gen.h>
#include <mem.h>
#include <util.h>

typedef struct Mesh Mesh;
struct Mesh
{
    unsigned int vertarr; /* vao */

    unsigned int vertbuf;
    unsigned int indxbuf;
    unsigned int normbuf;

    int vertsize;
    int indxsize;
    int normsize;
};

void
meshinit(Mesh *m, float *vert, int *indx, float *norm)
{
    m->vertsize = sizeof(float) * (int) *vert++;
    m->indxsize = sizeof(int)   *       *indx++;
    m->normsize = sizeof(float) * (int) *norm++;

    glGenVertexArrays(1, &(m->vertarr));
    glBindVertexArray(m->vertarr);

    /* vertex buffer */
    glGenBuffers(1, &(m->vertbuf));
    glBindBuffer(GL_ARRAY_BUFFER, m->vertbuf);
    glBufferData(GL_ARRAY_BUFFER, m->vertsize, vert, GL_STATIC_DRAW);

    /* index buffer */
    glGenBuffers(1, &(m->indxbuf));
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m->indxbuf);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, m->indxsize, indx, GL_STATIC_DRAW);

    /* normal buffer */
    glGenBuffers(1, &(m->normbuf));
    glBindBuffer(GL_ARRAY_BUFFER, m->normbuf);
    glBufferData(GL_ARRAY_BUFFER, m->normsize, norm, GL_STATIC_DRAW);
}

void
loadmesh(Mesh *m, char *fp)
{
    int i;
    int nvert, nindx, nnorm;
    char line[1024];
    char *end;
    FILE *f;

    /* mesh stuff */
    float   *vert;
    int     *indx;
    float   *norm;

    f = fopen(fp, "rb");
    if (f == NULL) {
        printf("unable to open file: %s, errno: %d\n", fp, errno);
        return;
    }

    fgets(line, sizeof(line), f); /* get first line */
    nvert = strtol(line, NULL, 10); /* TODO: check for errors? */
    vert = memalloc(sizeof(float) * nvert + 1);
    vert[0] = nvert;
    for (i = 0; i < (nvert / 3); i++) { /* get vertices */
        fgets(line, sizeof(line), f);
        *(vert + (3 * i + 1)) = strtof(line, &end);
        *(vert + (3 * i + 2)) = strtof(end, &end);
        *(vert + (3 * i + 3)) = strtof(end, &end);
        end = NULL;
    }

    fgets(line, sizeof(line), f);
    nindx = strtol(line, NULL, 10);
    indx = memalloc(sizeof(float) * nindx + 1);
    indx[0] = nindx;
    for (i = 0; i < (nindx / 3); i++) { /* get indices */
        fgets(line, sizeof(line), f);
        *(indx + (3 * i + 1)) = strtol(line, &end, 10);
        *(indx + (3 * i + 2)) = strtol(end, &end, 10);
        *(indx + (3 * i + 3)) = strtol(end, &end, 10);
        end = NULL;
    }

    fgets(line, sizeof(line), f);
    nnorm = strtol(line, NULL, 10);
    norm = memalloc(sizeof(float) * nnorm + 1);
    norm[0] = nnorm;
    for (i = 0; i < (nnorm / 3); i++) { /* get normals */
        fgets(line, sizeof(line), f);
        *(norm + (3 * i + 1)) = strtol(line, &end, 10);
        *(norm + (3 * i + 2)) = strtol(end, &end, 10);
        *(norm + (3 * i + 3)) = strtol(end, &end, 10);
        end = NULL;
    }
    fclose(f);

    meshinit(m, vert, indx, norm);

    memfree(vert);
    memfree(indx);
    memfree(norm);
}

void
drawmesh(Mesh *m)
{
    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);

    /* bind vertex buffer */
    glBindBuffer(GL_ARRAY_BUFFER, m->vertbuf);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);

    /* bind normal buffer */
    glBindRenderbuffer(GL_ARRAY_BUFFER, m->normbuf);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, 0);

    glDrawElements(GL_TRIANGLES, m->indxsize, GL_UNSIGNED_INT, 0);

    glDisableVertexAttribArray(0);
    glDisableVertexAttribArray(1);
}

void
delmesh(Mesh *m)
{
    glDisableVertexAttribArray(0);
    glDisableVertexAttribArray(1);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    glDeleteBuffers(1, &(m->vertbuf));
    glDeleteBuffers(1, &(m->indxbuf));

    glBindVertexArray(0);
    glDeleteVertexArrays(1, &(m->vertarr));
    memfree(m);
}

#endif