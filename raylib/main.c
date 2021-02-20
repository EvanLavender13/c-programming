#include <stdio.h>

#include <raylib.h>

#include <draw.h>
#include <interp.h>
#include <mem.h>

int
main()
{
    int width = 800;
    int height = 450;

    int n, ns;
    Vector2 *w, *p;

    InitWindow(width, height, "basic window");
    SetTargetFPS(60);
    while (!WindowShouldClose()) {
        BeginDrawing();
        ClearBackground(RAYWHITE);
        
        // set up control points / weights
        n = 4;
        w = memalloc(sizeof(*w) * n);
        w->x = 10;
        w->y = height - 10;
        (w + 1)->x = width - 10;
        (w + 1)->y = height - 10;
        (w + 2)->x = width - 10;
        (w + 2)->y = 10;
        (w + 3)->x = width / 2;
        (w + 3)->y = 10;

        ns = 25;
        p = memalloc(sizeof(*p) * ns);
        bezcurve(p, w, n, ns);
        drawbez(p, ns);

        memfree(p);
        memfree(w);

        EndDrawing();
    }

    TraceLog(LOG_INFO, "Reference count: %d", refcount);
    CloseWindow();

    return 0;
}
