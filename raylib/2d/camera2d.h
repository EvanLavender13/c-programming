#ifndef CAMERA_H_
#define CAMERA_H_

#include <raylib.h>

extern void
camera2d(Camera2D *c, float ox, float oy, float tx, float ty)
{
    c->offset.x = ox;
    c->offset.y = oy;
    c->target.x = tx;
    c->target.y = ty;
    c->rotation = 0.0;
    c->zoom = 1.0;
}

#endif