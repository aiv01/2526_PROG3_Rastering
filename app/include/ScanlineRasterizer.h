#pragma once
#include "Maths.h"
#include <raylib.h>
#include "Screen.h"
#include "TextureCpu.h"

enum GpuDrawMode {
    NONE,
    COLOR,
    TEXTURE
};

struct Gpu {
    TextureCpu* texture;
    GpuDrawMode mode;
    Vector3f point_light_pos;
    Vector3f camera_pos;
};

struct GpuVertex
{
    Vector2i screen_pos;
    Color color;
    float z_pos;
    Vector2f uv;
    Vector3f world_pos;
    Vector3f world_norm;
};

class ScanlineRasterizer {
public:
    static void rasterize(const Gpu& gpu, const GpuVertex& v1, const GpuVertex& v2, const GpuVertex& v3, Screen* screen);
};