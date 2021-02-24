#include <stdio.h>
#include <raylib.h>
#include <camera.h>
#include <mem.h>

int
main(int argc, char *argv[])
{
    const int W = 800;
    const int H = 600;

    /* camera stuff */
    Camera c;
    Vector3 pos, tar, up;
    Vector3 cube;

    pos.x = 0.0f;
    pos.y = 10.0f;
    pos.z = 10.0f;

    tar.x = 0.0f;
    tar.y = 0.0f;
    tar.z = 0.0f;

    up.x = 0.0f;
    up.y = 1.0f;
    up.z = 0.0f;

    c.position  = pos;
    c.target    = tar;
    c.up        = up;
    c.fovy      = 45.0f;
    c.type      = CAMERA_PERSPECTIVE;

    cube.x = 0.0f;
    cube.y = 0.0f;
    cube.z = 0.0f;

    InitWindow(W, H, "just a cube, lol");
    SetTargetFPS(60);
    //SetCameraMode(c, CAMERA_FREE);
    while (!WindowShouldClose()) {
        UpdateCamera(&c);

        BeginDrawing();
        ClearBackground(RAYWHITE);

        BeginMode3D(c);
        DrawCube(cube, 2.0f, 2.0f, 2.0f, RED);
        DrawGrid(10, 1.0f);
        EndMode3D();

        DrawFPS(10, 10);
        EndDrawing();
    }

    CloseWindow();

    TraceLog(LOG_INFO, "Reference count: %d", refcount);
    return 0;
}