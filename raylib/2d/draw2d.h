#ifndef DRAW_H_
#define DRAW_H_

extern void
drawbez(Vector2 *p, int ns, Color c)
{
    DrawLineStrip(p, ns, c);
}

extern void
drawgrid2d(float x, float y, int n, float sz)
{
    int i;
    float t, xv, yvt, yvb, yh, xhl, xhr;

    t = sz * (n / 2.0);
    xv = x- t;
    yvt = y - t;
    yvb = y + t;
    yh = yvt;
    xhl = xv;
    xhr = x + t;
    for (i = 0; i < n + 1; i++) {
        DrawLine(xv, yvt, xv, yvb, GRAY);
        DrawLine(xhl, yh, xhr, yh, GRAY);

        xv += sz;
        yh += sz;
    }
}

#endif