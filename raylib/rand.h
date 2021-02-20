#ifndef RAND_H_
#define RAND_H_

#include <mem.h>

extern void
randv(Vector2 *v, int n, int minx, int maxx, int miny, int maxy)
{
    int i;

    for (i = 0; i < n; i++) {
        (v + i)->x = GetRandomValue(minx, maxx);
        (v + i)->y = GetRandomValue(miny, maxy);
    }
}

#endif