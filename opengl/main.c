#include <stdio.h>

#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <mem.h>
#include <mesh.h>
#include <shader.h>

void
error()
{
    GLenum err;
    for (;;) {
        err = glGetError();
        if (err == GL_NO_ERROR) break;
        printf("ERROR: %d\n", err);
    }
}

GLFWwindow *
wininit(int width, int height)
{
    GLFWwindow *w;
    // some kind of hints?
    // TODO: find out what they do, lol
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    // this one seems obvious
    glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

    w = glfwCreateWindow(width, height, "window boy", NULL, NULL);
    return w;
}

void
winloop(GLFWwindow *w)
{
    Mesh *mesh;
    ShaderProg *sprog;

    sprog = memalloc(sizeof(*sprog));
    sproginit(sprog, "../shaders/vert.glsl", "../shaders/frag.glsl");
    linksprog(sprog);

    // triangle vertices
    // float v[] = {
    //      0.0f,  0.5f, 0.0f, // vertex 1
    //      0.5f, -0.5f, 0.0f, // vertex 2
    //     -0.5,  -0.5f, 0.0f  // vertex 3
    // };

    // quad vertices
    float v[] = {
        -0.5f,  0.5f, 0.0f,
        -0.5f, -0.5f, 0.0f,
         0.5f, -0.5f, 0.0f,
         0.5f,  0.5f, 0.0f,
    };

    int i[] = {
        0, 1, 3, 3, 1, 2
    };

    mesh = memalloc(sizeof(*mesh));
    meshinit(mesh, v, sizeof(v) / sizeof(float), i, sizeof(i) / sizeof(int));

    error();

    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    while (!glfwWindowShouldClose(w)) {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        glUseProgram(sprog->progid); // bind

        // draw mesh
        glBindVertexArray(mesh->vao);
        glEnableVertexAttribArray(0);
        //glDrawArrays(GL_TRIANGLES, 0, mesh->nvertices);
        glDrawElements(GL_TRIANGLES, mesh->nvertices, GL_UNSIGNED_INT, 0);

        // restore state
        glDisableVertexArrayAttrib(mesh->vao, 0);
        glBindVertexArray(0);

        glUseProgram(0); // unbind

        glfwSwapBuffers(w);
        glfwPollEvents();
    }

    delmesh(mesh);
    delsprog(sprog);

    glfwDestroyWindow(w);

    error();
}

int
main()
{
    GLFWwindow *w;

    glfwInit();

    w = wininit(800, 600);
    glfwMakeContextCurrent(w);
    glewExperimental = GL_TRUE;
    glewInit();
    winloop(w);

    glfwTerminate();

    printf("references remaining: %d\n", refcount);
    return 0;
}