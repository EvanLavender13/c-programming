#ifndef DRAW_H_
#define DRAW_H_

extern void
drawbez(Vector2 *p, int ns)
{
    DrawLineStrip(p, ns, BLUE);
}

#endif