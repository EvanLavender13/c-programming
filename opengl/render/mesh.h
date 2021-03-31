#ifndef MESH_H_
#define MESH_H_

#include <errno.h>
#include <stdio.h>

#include <GL/glew.h>

#include <mem.h>
#include <util.h>

typedef struct Mesh Mesh;
struct Mesh
{
    unsigned int vertarr; /* vao */
    int textureid;

    unsigned int vertbuf;
    unsigned int indxbuf;
    unsigned int normbuf;
    unsigned int texcbuf;

    int vertsize;
    int indxsize;
    int normsize;
    int texcsize;
};

void
meshinit(Mesh *m, float *vert, int *indx, float *norm, float *texc)
{
    m->vertsize = sizeof(float) * (int) *vert++;
    m->indxsize = sizeof(int)   *       *indx++;
    m->normsize = sizeof(float) * (int) *norm++;
    m->texcsize = sizeof(float) * (int) *texc++;
    m->textureid = 0;

    glGenVertexArrays(1, &(m->vertarr));
    glBindVertexArray(m->vertarr);

    /* vertex buffer */
    glGenBuffers(1, &(m->vertbuf));
    glBindBuffer(GL_ARRAY_BUFFER, m->vertbuf);
    glBufferData(GL_ARRAY_BUFFER, m->vertsize, vert, GL_STATIC_DRAW);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);

    /* index buffer */
    glGenBuffers(1, &(m->indxbuf));
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m->indxbuf);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, m->indxsize, indx, GL_STATIC_DRAW);

    /* normal buffer */
    glGenBuffers(1, &(m->normbuf));
    glBindBuffer(GL_ARRAY_BUFFER, m->normbuf);
    glBufferData(GL_ARRAY_BUFFER, m->normsize, norm, GL_STATIC_DRAW);
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, 0);

    /* texture coordinates buffer */
    glGenBuffers(1, &(m->texcbuf));
    glBindBuffer(GL_ARRAY_BUFFER, m->texcbuf);
    glBufferData(GL_ARRAY_BUFFER, m->texcsize, texc, GL_STATIC_DRAW);
    glEnableVertexAttribArray(2);
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 0, 0);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}

void
drawmesh(Mesh *m)
{
    if (m->textureid > 0) {
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, m->textureid);
    }

    glBindVertexArray(m->vertarr);

    glDrawElements(GL_TRIANGLES, m->indxsize, GL_UNSIGNED_INT, 0);

    glBindVertexArray(0);
}

void
delmesh(Mesh *m)
{
    glDisableVertexAttribArray(0);
    glDisableVertexAttribArray(1);
    glDisableVertexAttribArray(2);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    glDeleteBuffers(1, &(m->vertbuf));
    glDeleteBuffers(1, &(m->indxbuf));
    glDeleteBuffers(1, &(m->normbuf));
    glDeleteBuffers(1, &(m->texcbuf));

    glBindVertexArray(0);
    glDeleteVertexArrays(1, &(m->vertarr));
    memfree(m);
}

void
loadmesh(Mesh *m, char *fp)
{
    int i;
    int nvert, nindx, nnorm, ntexc;
    char line[1024];
    char *end;
    FILE *f;

    /* mesh stuff */
    float   *vert;
    int     *indx;
    float   *norm;
    float   *texc = NULL;

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
        // printf("%s", line);
        *(norm + (3 * i + 1)) = strtof(line, &end);
        *(norm + (3 * i + 2)) = strtof(end, &end);
        *(norm + (3 * i + 3)) = strtof(end, &end);
        end = NULL;
    }

    fgets(line, sizeof(line), f);
    ntexc = strtol(line, NULL, 10);
    if (ntexc > 0) {
        texc = memalloc(sizeof(float) * ntexc + 1);
        texc[0] = ntexc;
        for (i = 0; i < (ntexc / 2); i++) { /* get texture coordinates */
            fgets(line, sizeof(line), f);
            *(texc + (2 * i + 1)) = strtof(line, &end);
            *(texc + (2 * i + 2)) = strtof(end, &end);
        }
    } else {
        texc = memalloc(sizeof(float) * 1);
        texc[0] = 0;
    }

    fclose(f);

    meshinit(m, vert, indx, norm, texc);

    memfree(vert);
    memfree(indx);
    memfree(norm);
    memfree(texc);
}

#endif