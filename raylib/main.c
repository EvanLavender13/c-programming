#include <stdio.h>

#include <raylib.h>

#include <draw.h>
#include <interp.h>

int
main()
{
    int width = 800;
    int height = 450;

    int n, ns;
    Vector2 *w, *p;

    InitWindow(width, height, "basic window");
    SetTargetFPS(60);
    while (!WindowShouldClose())
    {
        BeginDrawing();
        ClearBackground(RAYWHITE);
        
        // set up control points / weights
        n = 4;
        w = MemAlloc(sizeof(*w) * n);
        w->x = 10;
        w->y = height - 10;
        (w+1)->x = width - 10;
        (w+1)->y = height - 10;
        (w+2)->x = width - 10;
        (w+2)->y = 10;
        (w+3)->x = width / 2;
        (w+3)->y = 10;
        
        ns = 10;
        p = bezcurve(w, n, ns);
        drawbez(p, ns);

        MemFree(p);
        MemFree(w);

        EndDrawing();
    }

    CloseWindow();

    return 0;
}
