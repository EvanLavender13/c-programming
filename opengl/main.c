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
#include <transform.h>

#include <texture.h>

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
    Mesh *mesh;
    MeshDef def;
    Model *model;
    ShaderProg *sprog;

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

    // cube vertices
    float v[] = {
        // V0
        -0.5f, 0.5f, 0.5f,
        // V1
        -0.5f, -0.5f, 0.5f,
        // V2
        0.5f, -0.5f, 0.5f,
        // V3
        0.5f, 0.5f, 0.5f,
        // V4
        -0.5f, 0.5f, -0.5f,
        // V5
        0.5f, 0.5f, -0.5f,
        // V6
        -0.5f, -0.5f, -0.5f,
        // V7
        0.5f, -0.5f, -0.5f,
        
        // For text coords in top face
        // V8: V4 repeated
        -0.5f, 0.5f, -0.5f,
        // V9: V5 repeated
        0.5f, 0.5f, -0.5f,
        // V10: V0 repeated
        -0.5f, 0.5f, 0.5f,
        // V11: V3 repeated
        0.5f, 0.5f, 0.5f,

        // For text coords in right face
        // V12: V3 repeated
        0.5f, 0.5f, 0.5f,
        // V13: V2 repeated
        0.5f, -0.5f, 0.5f,

        // For text coords in left face
        // V14: V0 repeated
        -0.5f, 0.5f, 0.5f,
        // V15: V1 repeated
        -0.5f, -0.5f, 0.5f,

        // For text coords in bottom face
        // V16: V6 repeated
        -0.5f, -0.5f, -0.5f,
        // V17: V7 repeated
        0.5f, -0.5f, -0.5f,
        // V18: V1 repeated
        -0.5f, -0.5f, 0.5f,
        // V19: V2 repeated
        0.5f, -0.5f, 0.5f
    };

    int i[] = {
        // Front face
        0, 1, 3, 3, 1, 2,
        // Top Face
        8, 10, 11, 9, 8, 11,
        // Right face
        12, 13, 7, 5, 12, 7,
        // Left face
        14, 15, 6, 4, 14, 6,
        // Bottom face
        16, 18, 19, 17, 16, 19,
        // Back face
        4, 6, 7, 5, 4, 7
    };

    // float c[] = {
    //     0.5f, 0.0f, 0.0f,
    //     0.0f, 0.5f, 0.0f,
    //     0.0f, 0.0f, 0.5f,
    //     0.0f, 0.5f, 0.5f,
    //     0.5f, 0.0f, 0.0f,
    //     0.0f, 0.5f, 0.0f,
    //     0.0f, 0.0f, 0.5f,
    //     0.0f, 0.5f, 0.5f,
    // };

    float t[] = {
        0.0f, 0.0f,
        0.0f, 0.5f,
        0.5f, 0.5f,
        0.5f, 0.0f,
        
        0.0f, 0.0f,
        0.5f, 0.0f,
        0.0f, 0.5f,
        0.5f, 0.5f,
        
        // For text coords in top face
        0.0f, 0.5f,
        0.5f, 0.5f,
        0.0f, 1.0f,
        0.5f, 1.0f,

        // For text coords in right face
        0.0f, 0.0f,
        0.0f, 0.5f,

        // For text coords in left face
        0.5f, 0.0f,
        0.5f, 0.5f,

        // For text coords in bottom face
        0.5f, 0.0f,
        1.0f, 0.0f,
        0.5f, 0.5f,
        1.0f, 0.5f
    };

    texid = texinit("../textures/grassblock.png");

    // define mesh
    // TODO: this structure is already annoying
    def.vertices = v;
    def.nvertices = sizeof(v) / sizeof(float);
    def.vsize = sizeof(float) * def.nvertices;
    def.indices = i;
    def.nindices = sizeof(i) / sizeof(int);
    def.isize = sizeof(int) * def.nindices;
    // def.colors = c;
    // def.ncolors = sizeof(c) / sizeof(float);
    // def.csize = sizeof(c) * def.ncolors;
    def.texcoords = t;
    def.ntexcoords = sizeof(t) / sizeof(float);
    def.tsize = sizeof(float) * def.ntexcoords;

    mesh = memalloc(sizeof(*mesh));
    meshinit(mesh, &def);

    model = memalloc(sizeof(*model));
    modelinit(model, mesh);
    model->pos[2] = -2.0f;

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
        float newrot = model->rot[0] + 1.0f;
        newrot = 45;
        if (newrot > 360)
            newrot = 0;

        setrotmodel(model, newrot, newrot, newrot);

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // TODO: move rendering stuff somewhere
        glUseProgram(sprog->progid); // bind

        // update projection matrix and set uniform
        updateproj(fov, width, height, znear, zfar);
        glUniformMatrix4fv(sprog->uproj,  1, GL_FALSE, &projection[0][0]);

        // set texture uniform
        glUniform1i(sprog->utex, 0);

        // update world matrix and set uniform
        // updateworld(model->pos, model->rot, model->scale);
        // glUniformMatrix4fv(sprog->uworld, 1, GL_FALSE, &world[0][0]);
        updateview(cam);
        updatemodelview(model);
        glUniformMatrix4fv(sprog->umv, 1, GL_FALSE, &modelview[0][0]);
        
        // activate texture
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, texid);

        // draw mesh
        glBindVertexArray(model->mesh->vao);
        // glEnableVertexAttribArray(0);
        // glEnableVertexAttribArray(1);
        
        //glDrawArrays(GL_TRIANGLES, 0, mesh->nvertices);
        glDrawElements(GL_TRIANGLES, model->mesh->nvertices, GL_UNSIGNED_INT, 0);

        // restore state
        // glDisableVertexArrayAttrib(model->mesh->vao, 0);
        // glDisableVertexArrayAttrib(model->mesh->vao, 1);
        glBindVertexArray(0);

        glUseProgram(0); // unbind

        glfwSwapBuffers(w);
        glfwPollEvents();
    }

    delmodel(model); // calls delmesh
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

    printf("references remaining: %d\n", refcount);
    return 0;
}