#ifndef INTERP_H_
#define INTERP_H_

#include <mem.h>

extern void
getuspace(float *u, int n)
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
    p->x = 5.0;
    p->y = 6.0;

    printf("n %d\n", n);
    if (n == 1)
    {

    }
    else 
    {
        decasteljaus(p, w, n - 1, u);
        decasteljaus(p, w + 1, n - 1, u);
    }
}

extern void
bezcurve(Vector2 *p, Vector2 *w, int n, int ns)
{
    int i;
    float *u;

    u = memalloc(sizeof(*u) * ns);
    getuspace(u, ns);
    for (i = 0; i < ns; i++)
        decasteljaus(p, w, n, *(u + i));
        // *(p + i) = *decasteljaus(p, w, n, *(u + i));

    memfree(u);
}

#endif