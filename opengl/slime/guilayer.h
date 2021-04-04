#ifndef GUI_LAYER_H_
#define GUI_LAYER_H_

#include <GL/glew.h>
#define NK_INCLUDE_FIXED_TYPES
#define NK_INCLUDE_STANDARD_IO
#define NK_INCLUDE_STANDARD_VARARGS
#define NK_INCLUDE_DEFAULT_ALLOCATOR
#define NK_INCLUDE_VERTEX_BUFFER_OUTPUT
#define NK_INCLUDE_FONT_BAKING
#define NK_INCLUDE_DEFAULT_FONT
#define NK_IMPLEMENTATION
#define NK_GLFW_GL3_IMPLEMENTATION
#define NK_KEYSTATE_BASED_INPUT
#include <nuklear.h>
#include <nuklear_glfw_gl3.h>

#include <mem.h>
#include <util.h>

#define MAX_VERTEX_BUFFER 512 * 1024
#define MAX_ELEMENT_BUFFER 128 * 1024

typedef struct nk_glfw nk_glfw;
typedef struct nk_context nk_context;
typedef struct nk_font_atlas nk_font_atlas;

typedef struct Gui Gui;
struct Gui
{
    nk_glfw        glfw;
    nk_context    *ctx;
    nk_font_atlas  atlas;
};

/* TODO: move this */
char str[40];
struct nk_colorf nkcolor = {1.0f, 1.0f, 1.0f, 1.0f};

void
guiinit(GLFWwindow *w, Gui *gui)
{
    int width, height;

    glfwGetWindowSize(w, &width, &height);

    /* TODO: find a way to handle input */
    gui->ctx = nk_glfw3_init(&(gui->glfw), w, NK_GLFW3_DEFAULT);
    nk_glfw3_font_stash_begin(&(gui->glfw), &(gui->atlas)); /* this is weird */
    nk_glfw3_font_stash_end(&(gui->glfw));
}

void
guiupdate(Gui *gui)
{
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    nk_glfw3_new_frame(&(gui->glfw));

    if (nk_begin(gui->ctx, "Demo", nk_rect(50, 50, 250, 400),
        NK_WINDOW_BORDER|NK_WINDOW_MOVABLE|NK_WINDOW_MINIMIZABLE|NK_WINDOW_TITLE)) {
        nk_layout_row_static(gui->ctx, 30, 225, 1);
        if (nk_button_label(gui->ctx, "Move")) {
            moveagents = !moveagents;
        }
        nk_slider_float(gui->ctx, 0.0f, &agentspeed, 30.0f, 0.1f);
        sprintf(str, "agentspeed %f", agentspeed);
        nk_label(gui->ctx, str, NK_TEXT_ALIGN_CENTERED);
        nk_slider_float(gui->ctx, 0.01f, &agentspacing, 10.0f, 0.01f);
        sprintf(str, "agentspacing %f", agentspacing);
        nk_label(gui->ctx, str, NK_TEXT_ALIGN_CENTERED);
        nk_slider_float(gui->ctx, 0.01f, &agentturning, 100.0f, 0.01f);
        sprintf(str, "agentturn %f", agentturning);
        nk_label(gui->ctx, str, NK_TEXT_ALIGN_CENTERED);
        nk_layout_row_dynamic(gui->ctx, 120, 1);
        nkcolor = nk_color_picker(gui->ctx, nkcolor, NK_RGBA);
        agentcolor[0] = nkcolor.r;
        agentcolor[1] = nkcolor.g;
        agentcolor[2] = nkcolor.b;
        agentcolor[3] = nkcolor.a;
    }
    nk_end(gui->ctx);

    nk_glfw3_render(&(gui->glfw), NK_ANTI_ALIASING_ON, MAX_VERTEX_BUFFER, MAX_ELEMENT_BUFFER);
}

void
guidel(Gui *gui)
{
    nk_glfw3_shutdown(&(gui->glfw));
    // memfree(gui->glfw);
    // memfree(gui->atlas);
    memfree(gui);
}

#endif