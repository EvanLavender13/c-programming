#ifndef DRAW_H_
#define DRAW_H_

extern void
drawbez(Vector2 *p, int ns, Color color)
{
    DrawLineStrip(p, ns, color);
}

#endif