#ifndef DRAW_H_
#define DRAW_H_

extern void
drawbez(Vector2 *p, int ns)
{
    int i;

    for (i = 0; i < ns; i++)
        printf("%d %f,%f\n", i, (p + i)->x, (p + i)->y);
        //DrawCircleV(*(p + i), 10, BLUE);
}

#endif