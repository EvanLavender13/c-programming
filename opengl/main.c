#include <stdio.h>

#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>

void
error()
{
    GLenum err;
    for (;;) {
        err = glGetError();
        if (err == GL_NO_ERROR) break;
        printf("Error: %d, %s\n", err, glewGetErrorString(err));
    }
}

GLFWwindow *
wininit()
{
    GLFWwindow *w;
    // some kind of hints?
    // TODO: find out what they do, lol
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    // this one seems obvious
    glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

    w = glfwCreateWindow(800, 600, "window boy", NULL, NULL);
    return w;
}

void
winloop(GLFWwindow *w)
{
    const GLchar *vsource, *fsource;
    GLint stat;

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

    // TODO: load shader from file
    vsource = R"glsl(
        #version 460 core

        in vec2 pos;

        void
        main()
        {
            gl_Position = vec4(pos, 0.0, 1.0);
        }
    )glsl";

    GLuint vshade = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vshade, 1, &vsource, NULL);
    glCompileShader(vshade);

    // TODO: load shader from file
    fsource = R"glsl(
        #version 460 core

        out vec4 outcolor;

        void
        main()
        {
            outcolor = vec4(1.0, 1.0, 0.0, 1.0);
        }
    )glsl";

    GLuint fshade = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fshade, 1, &fsource, NULL);
    glCompileShader(fshade);

    glGetShaderiv(vshade, GL_COMPILE_STATUS, &stat);
    printf("Vertex shader compiled: %d\n", stat);
    glGetShaderiv(fshade, GL_COMPILE_STATUS, &stat);
    printf("Fragment shader compiled: %d\n", stat);

    GLuint sprog = glCreateProgram();
    glAttachShader(sprog, vshade);
    glAttachShader(sprog, fshade);
    glLinkProgram(sprog);
    glUseProgram(sprog);

    // TODO: what this do?
    glBindFragDataLocation(sprog, 0, "outcolor");

    // TODO: what this do?
    GLint posattr = glGetAttribLocation(sprog, "pos");
    glVertexAttribPointer(posattr, 2, GL_FLOAT, GL_FALSE, 0, 0);
    glEnableVertexAttribArray(posattr);

    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    while (!glfwWindowShouldClose(w)) {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glDrawArrays(GL_TRIANGLES, 0, 3);
        glfwSwapBuffers(w);
        glfwPollEvents();
    }
}

int
main()
{
    GLFWwindow *w;

    glfwInit();

    w = wininit();
    glfwMakeContextCurrent(w);
    glewExperimental = GL_TRUE;
    glewInit();
    winloop(w);

    glfwTerminate();

    return 0;
}