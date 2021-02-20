#ifndef DRAW_H_
#define DRAW_H_

extern void
drawbez(Vector2 *p, int ns)
{
    int i;

    for (i = 0; i < ns; i++)
        DrawCircleV(*(p + i), 10, BLUE);
}

#endif