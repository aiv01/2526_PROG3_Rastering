#pragma once
#include "Maths.h"
#include <raylib.h>
#include "Screen.h"

class ScanlineRasterizer {
public:
    static void rasterize(const Vector2i& p1, const Vector2i& p2, const Vector2i& p3, const Color& color, Screen* screen);
};