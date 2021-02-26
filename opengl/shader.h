#ifndef SHADER_H_
#define SHADER_H_

#include <errno.h>
#include <stdio.h>

#include <GL/glew.h>

#include <mem.h>
#include <util.h>

char *
loadshaderf(char *fp)
{
    char *s;
    int sz;
    FILE *f;

    f = fopen(fp, "r");
    if (f == NULL)
        printf("unable to open file: %s, errno: %d\n", fp, errno);
    sz = fsize(f);
    s = memalloc(sz);
    fread(s, 1, sz, f);
    fclose(f);

    return s;
}



int
compileshader(const  char *src, int type)
{
    char err[4096];
    int s, stat;

    s = glCreateShader(type);
    glShaderSource(s, 1, &src, NULL);
    glCompileShader(s);
    glGetShaderiv(s, GL_COMPILE_STATUS, &stat);
    if (stat == GL_FALSE) {
        glGetShaderInfoLog(s, sizeof(err), NULL, err);
        printf("shader compile error: %s\n", err);
    }
    return s;
}

int
createshader(char *fp, int type)
{
    char *src;
    int s;

    src = loadshaderf(fp);
    s = compileshader(src, type);
    memfree(src);
    return s;
}

#endif
