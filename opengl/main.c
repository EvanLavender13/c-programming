#include <stdio.h>

#include <cglm/cglm.h>
#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <gen.h>
#include <mem.h>
#include <mesh.h>
#include <shader.h>
#include <transform.h>

GLFWwindow *
wininit(int width, int height)
{
    GLFWwindow *w;

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);
    w = glfwCreateWindow(width, height, "super window", NULL, NULL);

    return w;
}

void
winloop(GLFWwindow *w)
{
    int width, height;
    int fcount;
    float *vert, *color;
    double currtime, prevtime;

    Mesh *mesh;
    ShaderProg *sprog;

    /* begin init stuff */
    glfwGetWindowSize(w, &width, &height);

    // vert = memalloc(sizeof(float) * 9 + 1); /* sneak size in there */
    // gentri(vert);
    vert = memalloc(sizeof(float) * 108 + 1);
    gencube(vert);

    color = memalloc(sizeof(float) * 108 + 1);
    genrandcolr(color, 108);

    sprog = memalloc(sizeof(ShaderProg));
    sproginit(sprog, "../shaders/vert.glsl", "../shaders/frag.glsl");
    linksprog(sprog);

    // TODO: add to shader prog or something
    sprog->unimvp = glGetUniformLocation(sprog->progid, "mvp");

    mesh = memalloc(sizeof(Mesh));
    meshinit(mesh, vert, color);
    /* end init stuff */

    prevtime = glfwGetTime();
    fcount = 0;

    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    while (!glfwWindowShouldClose(w)) {
        // TODO: move FPS stuff
        currtime = glfwGetTime();
        fcount++;
        if (currtime - prevtime >= 1.0)
        {
            printf("%f ms/frame %d fps\n", 1000.0 / fcount, fcount);
            fcount = 0;
            prevtime += 1.0;
        }

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        glUseProgram(sprog->progid); // bind

        /* begin do stuff */

        updateproj(glm_rad(45.0f), (float) width / (float) height, 0.1f, 100.0f);
        updateview((vec3) {4.0f, 3.0f, 3.0f}, (vec3) {0.0f, 0.0f, 0.0f}, (vec3) {0.0f, 1.0f, 0.0f});
        updatemodel();
        updatemvp();
        glUniformMatrix4fv(sprog->unimvp, 1, GL_FALSE, &tmvp[0][0]);

        drawmesh(mesh);

        /* end do stuff */

        glUseProgram(0); // unbind

        glfwSwapBuffers(w);
        glfwPollEvents();
    }

    /* begin free stuff */
    delsprog(sprog);
    delmesh(mesh);

    memfree(vert);
    memfree(color);
    /* end free stuff */

    glfwDestroyWindow(w);
}

int
main()
{
    GLFWwindow *w;

    glfwInit();

    w = wininit(800, 600);
    glfwMakeContextCurrent(w);
    glewExperimental = GL_TRUE; // TODO: what is this?
    glewInit();
    winloop(w);

    glfwTerminate();

    printf("references remaining: %d\n", nrefs);
    return 0;
}