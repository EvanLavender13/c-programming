#ifndef INTERP_H_
#define INTERP_H_

#include <mem.h>

extern void
uspace(float *u, int n)
{
    float s;
    int i;

    *u = 0.0f;
    s = 1.0f / (n - 1);
    for (i = 1; i < n; i++)
        *(u + i) = *(u + i - 1) + s;
}

extern void
linearv(Vector2 *pu, Vector2 *p0, Vector2 *p1, float u)
{
    pu->x = (1 - u) * p0->x + u * p1-> x;
    pu->y = (1 - u) * p0->y + u * p1-> y;
}

extern void
decasteljaus(Vector2 *p, Vector2 *w, int n, float u)
{
    Vector2 *p0, *p1;

    if (n == 1)
        *p = *w;
    else {
        p0 = memalloc(sizeof(*p0));
        decasteljaus(p0, w, n - 1, u);
        p1 = memalloc(sizeof(*p1));
        decasteljaus(p1, w + 1, n - 1, u);
        linearv(p, p0, p1, u);
        memfree(p0);
        memfree(p1);
    }
}

extern void
bezcurve(Vector2 *p, Vector2 *w, int n, int ns)
{
    int i;
    float *u;

    u = memalloc(sizeof(*u) * ns);
    uspace(u, ns);
    for (i = 0; i < ns; i++)
        decasteljaus(p + i, w, n, *(u + i));
    memfree(u);
}

#endif