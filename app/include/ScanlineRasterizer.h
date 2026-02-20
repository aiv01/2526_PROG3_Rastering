#pragma once
#include "Maths.h"
#include <raylib.h>
#include "Screen.h"

struct GpuVertex
{
    Vector2i screen_pos;
    Color color;
    float z_pos;
};

class ScanlineRasterizer {
public:
    static void rasterize(const GpuVertex& v1, const GpuVertex& v2, const GpuVertex& v3, Screen* screen);
};