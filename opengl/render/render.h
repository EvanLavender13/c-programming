#ifndef RENDER_H_
#define RENDER_H_

#include <GL/glew.h>

void
renderinit()
{
    glEnable(GL_DEPTH_TEST);
    // glEnable(GL_CULL_FACE);
    // glCullFace(GL_FRONT);
    glDepthFunc(GL_LESS);
    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    
}

void
renderviewport(int x, int y, int width, int height)
{
    glViewport(x, y, width, height);
}

void
renderclearcolor(float r, float g, float b, float a)
{
    glClearColor(r, g, b, a);
}

void
renderclear()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void
renderbegin()
{
    renderclearcolor(0.1f, 0.1f, 0.1f, 1.0f);
    renderclear();
}

void
renderend()
{
    glBindVertexArray(0); // restore state
    glUseProgram(0);      // unbind
}

#endif