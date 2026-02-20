#pragma once
#include "Maths.h"
#include <raylib.h>
#include "Screen.h"
#include "TextureCpu.h"

struct Gpu {
    TextureCpu* texture;
};

struct GpuVertex
{
    Vector2i screen_pos;
    Color color;
    float z_pos;
    Vector2f uv;
};

class ScanlineRasterizer {
public:
    static void rasterize(const Gpu& gpu, const GpuVertex& v1, const GpuVertex& v2, const GpuVertex& v3, Screen* screen);
};