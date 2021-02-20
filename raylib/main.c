#include <stdio.h>

#include <raylib.h>
#include <raymath.h>

#include <camera.h>
#include <draw.h>
#include <interp.h>
#include <mem.h>
#include <rand.h>

int
main(int argc, char *argv[])
{
    int width = 800;
    int height = 450;

    int cg, n, ns;
    Camera2D *c;
    Vector2 *w, *p, *tp;

    SetConfigFlags(FLAG_MSAA_4X_HINT);
    InitWindow(width, height, "basic window");

    c = memalloc(sizeof(*c));
    camera2d(c, width / 2, height / 2, width / 2, height / 2);

    n = 10;
    w = memalloc(sizeof(*w) * n);

    ns = 100;
    p = memalloc(sizeof(*p) * ns);

    tp = memalloc(sizeof(*tp));

    SetTargetFPS(60);
    while (!WindowShouldClose()) {
        c->zoom += GetMouseWheelMove() * 0.05;
        c->zoom = Clamp(c->zoom, 0.1, 3.0);

        if (IsKeyReleased(KEY_SPACE))
        {
            randv(w, n, 0, width, 0, height);
            bezcurve(p, w, n, ns);
        }

        cg = GetGestureDetected();
        if (cg == GESTURE_DRAG)
        {
            *tp = GetTouchPosition(0);
        }

        if (IsKeyDown(KEY_A))
            c->target.x -= 100 * GetFrameTime();

        if (IsKeyDown(KEY_D))
            c->target.x += 100 * GetFrameTime();

        if (IsKeyDown(KEY_W))
            c->target.y -= 100 * GetFrameTime();

        if (IsKeyDown(KEY_S))
            c->target.y += 100 * GetFrameTime();

        BeginDrawing();
        ClearBackground(RAYWHITE);
        
        BeginMode2D(*c);
        drawbez(p, ns);
        DrawLine(c->target.x, -height * 10, c->target.x, height * 10, GREEN);
        DrawLine(-width * 10, c->target.y, width * 10, c->target.y, GREEN);
        EndMode2D();
        
        DrawFPS(10, 10);
        EndDrawing();
    }

    memfree(c);
    memfree(w);
    memfree(p);
    memfree(tp);

    //TakeScreenshot("thinger.png");
    TraceLog(LOG_INFO, "Reference count: %d", refcount);
    CloseWindow();

    return 0;
}
