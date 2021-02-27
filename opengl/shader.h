#ifndef SHADER_H_
#define SHADER_H_

#include <errno.h>
#include <stdio.h>
// TODO: temporary
#include <string.h>

#include <GL/glew.h>
#include <cglm/cglm.h>

#include <mem.h>
#include <util.h>

typedef struct ShaderProg ShaderProg;
struct ShaderProg
{
    int progid;
    int vertid;
    int fragid;

    int uproj;
    int uworld;
};

int
compileshader(const char *src, int type)
{
    int shader;

    shader = glCreateShader(type);
    // TODO: error check shader
    glShaderSource(shader, 1, &src, NULL);
    glCompileShader(shader);
    return shader;
}

int
createshader(char *fp, int type)
{  
    char err[4096];
    char *src;
    int size, shader, stat;
    FILE *f;

    // load shader source from file
    f = fopen(fp, "r");
    if (f == NULL)
        printf("unable to open file: %s, errno: %d\n", fp, errno);
    size = fsize(f);
    src = memalloc(size + 1); // alloc src
    fread(src, 1, size, f);
    src[size] = 0; // null terminated
    fclose(f);

    // compile shader from source
    shader = compileshader(src, type);
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
    sprog->vertid = createshader(vertfp, GL_VERTEX_SHADER);
    sprog->fragid = createshader(fragfp, GL_FRAGMENT_SHADER);

    glAttachShader(sprog->progid, sprog->vertid);
    glAttachShader(sprog->progid, sprog->fragid);
}

void
linksprog(ShaderProg *sprog)
{
    glLinkProgram(sprog->progid);
    // TODO: error check link status

    // https://stackoverflow.com/a/9117411
    glDetachShader(sprog->progid, sprog->vertid);
    glDetachShader(sprog->progid, sprog->fragid);
    glDeleteShader(sprog->vertid);
    glDeleteShader(sprog->fragid);

    glValidateProgram(sprog->progid);
    // TODO: error check validate status
}

void
delsprog(ShaderProg *sprog)
{
    glDeleteProgram(sprog->progid);
    glDeleteShader(sprog->vertid);
    glDeleteShader(sprog->fragid);
    memfree(sprog);
}

// TODO: need to allow more than 1 uniform
void
createuniform(ShaderProg *sprog, const char *uname)
{
    int u;

    u = glGetUniformLocation(sprog->progid, uname);
    // TODO: temporary
    if (strcmp(uname, "projection") == 0)
        sprog->uproj = u;
    else if (strcmp(uname, "world") == 0)
        sprog->uworld = u;
}

// TODO: need to allow more than 1 uniform
// void
// setuniform(ShaderProg *sprog, mat4 *mat)
// {
//     // TODO: error check uniform location
    
// }

#endif
