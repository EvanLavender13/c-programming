#include <stdio.h>

#include <cglm/cglm.h>
#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <camera.h>
#include <context.h>
#include <input.h>
#include <mem.h>
#include <mesh.h>
#include <model.h>
#include <shader.h>
#include <things.h>
#include <transform.h>
#include <window.h>

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

void
loop(GLFWwindow *winhandle)
{
    int width, height;
    int fcount;
    double currtime, prevtime, lasttime;
    double delta;

    // vec3 lightpos = {0.0f, 0.0f, 0.0f};
    Camera *cam;
    ShaderProg *sprog;
    Thing *t;

    /* begin init stuff */
    glfwGetWindowSize(winhandle, &width, &height);

    sprog = memalloc(sizeof(ShaderProg));
    sproginit(sprog, "../assets/shaders/vert.glsl", "../assets/shaders/frag.glsl");
    sproglink(sprog);

    // TODO: add to shader prog or something?
    sprog->umvp    = glGetUniformLocation(sprog->progid, "tmvp");
    sprog->uobjcol = glGetUniformLocation(sprog->progid, "objcolor");
 
    cam = memalloc(sizeof(*cam));
    caminit(cam);
    inputinit(winhandle);
    thingsinit();

    poscam(cam, 0.0f, 0.0f, -3.0f);
    /* end init stuff */

    prevtime = glfwGetTime();
    currtime = glfwGetTime();
    fcount = 0;

    glEnable(GL_DEPTH_TEST);
    // glEnable(GL_CULL_FACE);
    // glCullFace(GL_FRONT);
    glDepthFunc(GL_LESS);
    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
    do {
        // TODO: move FPS stuff
        lasttime = currtime;
        currtime = glfwGetTime();
        fcount++;
        if (currtime - prevtime >= 1.0)
        {
            // printf("%f ms/frame %d fps\n", 1000.0 / fcount, fcount);
            fcount = 0;
            prevtime += 1.0;
        }
        delta = currtime - lasttime;

        input(winhandle);
        movecam(cam, movev[0] * 0.05f, movev[1] * 0.05f, movev[2] * 0.05f);
        if (rmouse)
            rotcam(cam, displayv[0] * 0.2f, displayv[1] * 0.2f, 0);

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        glUseProgram(sprog->progid); // bind

        /* begin do stuff */
        glUniform4f(sprog->uobjcol, 1.0f, 0.5f, 0.31f, 1.0f);

        updateproj(glm_rad(45.0f), (float) width / (float) height, 0.1f, 100.0f);
        updateview(cam);

        t = allthings;
        while (t != NULL) {
            float newrot = t->model->rot[0] + 1.0f;
            if (newrot > 360.0f) newrot = 0.0f;
            // setrotmodel(t->model, newrot, 0.0f, 0.0f);
            updatemodel(t->model);
            updatemvp();
            glUniformMatrix4fv(sprog->umvp, 1, GL_FALSE, &tmvp[0][0]);
            drawmodel(t->model);
            t = t->next;
        }

        /* end do stuff */
        glBindVertexArray(0); // restore state
        glUseProgram(0);      // unbind

        winupdate(winhandle);
    } while (glfwGetKey(winhandle, GLFW_KEY_ESCAPE) != GLFW_PRESS && glfwWindowShouldClose(winhandle) == 0);

    /* begin free stuff */
    sprogdel(sprog);
    memfree(cam);
    delthings();
    /* end free stuff */

    error();
}

int
main()
{
    GLFWwindow *winhandle;

    winhandle = wininit(1200, 800);
    loop(winhandle);
    windel(winhandle);

    printf("references remaining: %d\n", nrefs);
    return 0;
}