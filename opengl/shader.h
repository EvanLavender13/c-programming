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
    char *src;
    int sz;
    FILE *f;

    f = fopen(fp, "r");
    if (f == NULL)
        printf("unable to open file: %s, errno: %d\n", fp, errno);
    sz = fsize(f);
    src = memalloc(sz);
    fread(src, 1, sz, f);
    fclose(f);

    return src;
}



int
compileshader(const  char *src, int type)
{
    char err[4096];
    int sh, stat;

    sh = glCreateShader(type);
    glShaderSource(sh, 1, &src, NULL);
    glCompileShader(sh);
    glGetShaderiv(sh, GL_COMPILE_STATUS, &stat);
    if (stat == GL_FALSE) {
        glGetShaderInfoLog(sh, sizeof(err), NULL, err);
        printf("shader compile error: %s\n", err);
    }
    return sh;
}

int
createshader(char *fp, int type)
{
    char *src;
    int sh;

    src = loadshaderf(fp);
    sh = compileshader(src, type);
    memfree(src);
    return sh;
}

#endif
