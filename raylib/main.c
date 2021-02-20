#include <stdio.h>

#include <raylib.h>

#include <draw.h>
#include <interp.h>
#include <mem.h>
#include <rand.h>

int
main(int argc, char *argv[])
{
    int width = 800;
    int height = 450;

    int i, n, ns;
    Vector2 *w, *p;

    i = 0;
    InitWindow(width, height, "basic window");
    SetTargetFPS(60);
    while (!WindowShouldClose()) {
        BeginDrawing();
        ClearBackground(RAYWHITE);
        
        n = 4;
        w = memalloc(sizeof(*w) * n);
        randv(w, n, 0, width, 0, height);

        ns = 25;
        p = memalloc(sizeof(*p) * ns);
        bezcurve(p, w, n, ns);
        drawbez(p, ns);

        memfree(w);
        memfree(p);
        
        EndDrawing();
    }

    //TakeScreenshot("thinger.png");
    TraceLog(LOG_INFO, "Reference count: %d", refcount);
    CloseWindow();

    return 0;
}
