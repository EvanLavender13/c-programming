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

    int n, ns;
    Camera2D *c;
    Vector2 *w, *p;

    /* gestures */
    int cg, pf;
    Vector2 *ptp, *ctp; /* touch positions */

    SetConfigFlags(FLAG_MSAA_4X_HINT);
    InitWindow(width, height, "basic window");

    c = memalloc(sizeof(*c));
    camera2d(c, width / 2, height / 2, width / 2, height / 2);

    n = 4;
    w = memalloc(sizeof(*w) * n);

    ns = 100;
    p = memalloc(sizeof(*p) * ns);

    pf = 0;
    ctp = memalloc(sizeof(*ctp));
    ptp = memalloc(sizeof(*ptp));

    SetTargetFPS(60);
    while (!WindowShouldClose()) {
        c->zoom += GetMouseWheelMove() * 0.05;
        c->zoom = Clamp(c->zoom, 0.1, 3.0);

        cg = GetGestureDetected();
        if (cg == GESTURE_DRAG) {
            *ptp = *ctp;
            *ctp = GetTouchPosition(0);
            if (pf) {
                c->target.x += ptp->x - ctp->x;
                c->target.y += ptp->y - ctp->y;
            }
            pf = 1;
            
        } else
            pf = 0;

        if (IsKeyReleased(KEY_SPACE)) {
            randv(w, n, 0, width, 0, height);
            bezcurve(p, w, n, ns);
        }

        BeginDrawing();
        ClearBackground(RAYWHITE);
        
        BeginMode2D(*c);
        drawbez(p, ns, RED);
        DrawLine(c->target.x, -height * 10, c->target.x, height * 10, GREEN);
        DrawLine(-width * 10, c->target.y, width * 10, c->target.y, GREEN);

        //DrawLine(c->offset.x, -height * 10, c->offset.x, height * 10, BLUE);
        //DrawLine(-width * 10, c->offset.y, width * 10, c->offset.y, BLUE);
        EndMode2D();
        
        DrawFPS(10, 10);
        EndDrawing();
    }

    memfree(c);
    memfree(w);
    memfree(p);
    memfree(ctp);
    memfree(ptp);

    //TakeScreenshot("thinger.png");
    TraceLog(LOG_INFO, "Reference count: %d", refcount);
    CloseWindow();

    return 0;
}
