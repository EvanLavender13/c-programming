#ifndef SHADER_H_
#define SHADER_H_

#include <errno.h>
#include <stdio.h>

#include <GL/glew.h>

#include <mem.h>
#include <util.h>

typedef struct ShaderProg ShaderProg;
struct ShaderProg
{
    int progid;
    int vertid;
    int fragid;

    int uviewprojection; /* view-projection matrix uniform */
    int utransform;      /* transform matrix uniform */
    int uobjcolor;       /* object color uniform */
};

int
shadercomp(const char *src, int type)
{
    int shader;

    shader = glCreateShader(type);
    // TODO: error check shader
    glShaderSource(shader, 1, &src, NULL);
    glCompileShader(shader);
    return shader;
}

int
shaderinit(char *fp, int type)
{  
    char err[4096];
    char *src;
    int size, shader, stat;
    FILE *f;

    // load shader source from file
    f = fopen(fp, "r");
    if (f == NULL) {
        printf("unable to open file: %s, errno: %d\n", fp, errno);
        return 0;
    }
    size = fsize(f);
    src = memalloc(size + 1); // alloc src
    fread(src, 1, size, f);
    src[size] = 0; // null terminated
    fclose(f);

    // compile shader from source
    shader = shadercomp(src, type);
    glGetShaderiv(shader, GL_COMPILE_STATUS, &stat);
    if (stat == GL_FALSE) {
        glGetShaderInfoLog(shader, sizeof(err), NULL, err);
        printf("shader compile error in %s: %s\n", fp, err);
    }

    memfree(src); // free src

    return shader;
}

// TODO: not sure I like this function
void
sproginit(ShaderProg *sprog, char *vertfp, char *fragfp)
{
    sprog->progid = glCreateProgram();
    // TODO: error check progid
    sprog->vertid = shaderinit(vertfp, GL_VERTEX_SHADER);
    sprog->fragid = shaderinit(fragfp, GL_FRAGMENT_SHADER);

    glAttachShader(sprog->progid, sprog->vertid);
    glAttachShader(sprog->progid, sprog->fragid);
}

void
sproglink(ShaderProg *sprog)
{
    char err[4096];
    int stat;

    glLinkProgram(sprog->progid);
    glGetProgramiv(sprog->progid, GL_LINK_STATUS, &stat);
    if (stat == GL_FALSE) {
        glGetProgramInfoLog(sprog->progid, sizeof(err), NULL, err);
        printf("shader link error: %s\n", err);
    }

    // https://stackoverflow.com/a/9117411
    glDetachShader(sprog->progid, sprog->vertid);
    glDetachShader(sprog->progid, sprog->fragid);
    glDeleteShader(sprog->vertid);
    glDeleteShader(sprog->fragid);

    glValidateProgram(sprog->progid);
    glGetProgramiv(sprog->progid, GL_VALIDATE_STATUS, &stat);
    if (stat == GL_FALSE) {
        glGetProgramInfoLog(sprog->progid, sizeof(err), NULL, err);
        printf("shader validation error: %s\n", err);
    }
}

void
sprogdel(ShaderProg *sprog)
{
    glDeleteProgram(sprog->progid);
    memfree(sprog);
}

#endif
