#pragma once
#include "Maths.h"
#include <raylib.h>
#include "Screen.h"

class ShapeRasterizer {
public:
    static void dda_line_raster(int x1, int y1, int x2, int y2, Color color, Screen* screen);
    static void bbox_triangle_raster(Vector2i p1, Vector2i p2, Vector2i p3, Color color, Screen* screen);
private:
    static bool bbox_is_point_in_triangle(Vector2i p, Vector2i a, Vector2i b, Vector2i c);
};