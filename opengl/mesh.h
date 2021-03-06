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
    unsigned int colrbuf;

    int vertsize;
    int indxsize;
    int colrsize;
};

void
meshinit(Mesh *m, float *vert, int *indx, float *colr)
{
    m->vertsize = sizeof(float) * (int) *vert++;
    m->indxsize = sizeof(int)   *       *indx++;
    m->colrsize = sizeof(float) * (int) *colr++;

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

    glGenBuffers(1, &(m->colrbuf));
    glBindBuffer(GL_ARRAY_BUFFER, m->colrbuf);
    glBufferData(GL_ARRAY_BUFFER, m->colrsize, colr, GL_STATIC_DRAW);
}

void
loadmesh(Mesh *m, char *fp)
{
    int i;
    int nvert, nindx;
    char line[1024];
    char *end;
    FILE *f;

    /* mesh stuff */
    float   *vert;
    int     *indx;
    float   *colr;

    f = fopen(fp, "rb");
    if (f == NULL) {
        printf("unable to open file: %s, errno: %d\n", fp, errno);
        return;
    }

    fgets(line, sizeof(line), f); /* get first line */
    nvert = strtol(line, NULL, 10); /* TODO: check for errors? */
    vert = memalloc(sizeof(float) * nvert * 3 + 1);
    vert[0] = nvert * 3;
    for (i = 0; i < nvert; i++) { /* get vertices */
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
    fclose(f);

    /* TODO: do something with color */
    colr = memalloc(sizeof(float) * nvert * 3 + 1);
    genrandcolr(colr, nvert * 3);    

    meshinit(m, vert, indx, colr);

    // printarrf(vert, nvert * 3 + 1);
    // printarri(indx, nindx + 1);
    // printarrf(colr, nvert * 3 + 1);
    memfree(vert);
    memfree(indx);
    memfree(colr);
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
    glDeleteBuffers(1, &(m->colrbuf));

    glBindVertexArray(0);
    glDeleteVertexArrays(1, &(m->vertarr));
    memfree(m);
}

#endif