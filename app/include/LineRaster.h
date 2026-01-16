#pragma once
#include <cmath>
#include <raylib.h>
#include "Screen.h"

void dda_line_raster(int x1, int y1, int x2, int y2, Color color, Screen* screen) 
{
    int dx = abs(x1 - x2);
    int dy = abs(y1 - y2);

    int steps = (dx < dy) ? dy : dx;

    int sx = (x1 < x2) ? 1 : -1;
    int sy = (y1 < y2) ? 1 : -1;

    float steps_x = (float)dx / (float)steps * (float)sx;
    float steps_y = (float)dy / (float)steps * (float)sy;

    float x = x1;
    float y = y1;
    for(int i=0; i <= steps; ++i) {

        //DrawPixel((int)x, (int)y, color);
        screen->put_pixel((int)x, (int)y, color);
        x += steps_x;
        y += steps_y;
    }
}
