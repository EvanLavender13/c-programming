#ifndef INTERP_H_
#define INTERP_H_

#include <raylib.h>

extern float *
getuspace(int n)
{
    float *u;
    float s;
    int i;

    u = MemAlloc(sizeof(*u) * n);
    *u = 0.0f;
    s = 1.0f / (n - 1);
    for (i = 1; i < n; i++)
        *(u + i) = *(u + i - 1) + s;
    
    return u;
}

extern Vector2 *
linearv(Vector2 *p0, Vector2 *p1, float u)
{
    Vector2 *p;

    p = MemAlloc(sizeof(*p));
    p->x = (1 - u) * p0->x + u * p1-> x;
    p->y = (1 - u) * p0->y + u * p1-> y;
    return p;
}

extern Vector2 *
decasteljaus(Vector2 *p, int n, float u)
{
    Vector2 *r, *p0, *p1;

    if (n == 1)
        r = p;
    else 
    {
        p0 = decasteljaus(p, n - 1, u);
        p1 = decasteljaus(p + 1, n - 1, u);
        r = linearv(p0, p1, u);

        if (n > 2)
        {
            MemFree(p0);
            MemFree(p1);
        }
    }

    return r;
}

extern Vector2 *
bezcurve(Vector2 *w, int n, int ns)
{
    int i;
    float *u;
    Vector2 *p;

    u = getuspace(ns);
    p = MemAlloc(sizeof(*p) * ns);
    for (i = 0; i < ns; i++)
        *(p + i) = *decasteljaus(w, n, *(u + i));

    MemFree(u);
    return p;
}

#endif