#include <stdio.h>

#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <mem.h>
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
    int vs, fs;

    // triangle vertices
    float v[] = {
         0.0f,  0.5f, // vertex 1
         0.5f, -0.5f, // vertex 2
        -0.5,  -0.5f  // vertex 3
    };

    // vertex array
    // TODO: what this do?
    GLuint vao;
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);

    // vertex buffer
    // TODO: what this do?
    GLuint vbo;
    glGenBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(v), v, GL_STATIC_DRAW);

    vs = createshader("../shaders/vert.glsl", GL_VERTEX_SHADER);
    fs = createshader("../shaders/frag.glsl", GL_FRAGMENT_SHADER);

    GLuint sprog = glCreateProgram();
    glAttachShader(sprog, vs);
    glAttachShader(sprog, fs);
    glLinkProgram(sprog);
    glUseProgram(sprog);

    // TODO: what this do?
    glBindFragDataLocation(sprog, 0, "outcolor");

    // TODO: what this do?
    GLint posattr = glGetAttribLocation(sprog, "pos");
    glVertexAttribPointer(posattr, 2, GL_FLOAT, GL_FALSE, 0, 0);
    glEnableVertexAttribArray(posattr);

    error();

    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    while (!glfwWindowShouldClose(w)) {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glDrawArrays(GL_TRIANGLES, 0, 3);
        glfwSwapBuffers(w);
        glfwPollEvents();
    }

    glDeleteProgram(sprog);
    glDeleteShader(vs);
    glDeleteShader(fs);

    glDeleteBuffers(1, &vbo);
    glDeleteVertexArrays(1, &vao);

    glfwDestroyWindow(w);
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