#include <stdio.h>

#define GLEW_STATIC
#include <cglm/cglm.h>
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <camera.h>
#include <mem.h>
#include <mesh.h>
#include <model.h>
#include <mouse.h>
#include <shader.h>
#include <texture.h>
#include <things.h>
#include <transform.h>


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

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);
    w = glfwCreateWindow(width, height, "super window", NULL, NULL);

    // init mouse input
    mouseinit(w);

    return w;
}

void
winloop(GLFWwindow *w)
{
    int width, height;
    float fov, znear, zfar;

    int texid;
    Camera *cam;
    ShaderProg *sprog;
    Thing *t;

    fov = glm_rad(60.0f);
    znear = 0.01f;
    zfar = 1000.0f;
    glfwGetWindowSize(w, &width, &height);

    // create and link shader program
    sprog = memalloc(sizeof(*sprog));
    sproginit(sprog, "../shaders/vert.glsl", "../shaders/frag.glsl");
    linksprog(sprog);

    // create uniforms
    createuniform(sprog, "projection");
    // createuniform(sprog, "world");
    createuniform(sprog, "modelview");
    createuniform(sprog, "texture");

    texid = texinit("../textures/grassblock.png");

    thingsinit();

    cam = memalloc(sizeof(*cam));
    caminit(cam);

    // TODO: move FPS stuff
    double prevtime = glfwGetTime();
    double currtime;
    int fcount = 0;
    
    glEnable(GL_DEPTH_TEST);
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

        // TODO: do input somewhere
        inputmouse();

        //printf("rmouse %d\n", rmouse);
        if (rmouse)
            rotcam(cam, display[0] * 0.2f, display[1] * 0.2f, 0);

        // TODO: rotate cube somewhere else, lol
        // float newrot = allthings->rot[0] + 1.0f;
        // if (newrot > 360)
        //     newrot = 0;

        // setrotmodel(allthings, newrot, newrot, newrot);

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // TODO: move rendering stuff somewhere
        glUseProgram(sprog->progid); // bind

        // update projection matrix and set uniform
        updateproj(fov, width, height, znear, zfar);
        glUniformMatrix4fv(sprog->uproj,  1, GL_FALSE, &projection[0][0]);

        // set texture uniform
        glUniform1i(sprog->utex, 0);
        // update model view
        updateview(cam);

        t = allthings;
        // for (i = 0; i < nthings; i++) {
        while (t != NULL) {
            updatemodelview(t->model);
            glUniformMatrix4fv(sprog->umv, 1, GL_FALSE, &modelview[0][0]);
            
            // activate texture
            glActiveTexture(GL_TEXTURE0);
            glBindTexture(GL_TEXTURE_2D, texid);
            // draw mesh
            // TODO: this is weird
            glBindVertexArray(t->model->mesh->vao);
            glDrawElements(GL_TRIANGLES, t->model->mesh->nvertices, GL_UNSIGNED_INT, 0);
            t = t->next;
        }
        
        glBindVertexArray(0);   // restore state
        glUseProgram(0);        // unbind

        glfwSwapBuffers(w);
        glfwPollEvents();
    }

    delthings();
    delsprog(sprog);
    memfree(cam);

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

    printf("things remaining: %d\n", nthings);
    printf("references remaining: %d\n", nrefs);
    return 0;
}