#pragma once
#include "Maths.h"
#include <raylib.h>
#include "Screen.h"
#include "TextureCpu.h"

enum GpuDrawMode {
    NONE,
    COLOR,
    TEXTURE,
    TEXTURE_VERTEX_COLOR
};

struct Gpu {
    TextureCpu* texture;
    GpuDrawMode mode;
    Vector3f point_light_pos;
    Vector3f camera_pos;
    Color light_color;
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

static inline uint8_t clamp_u8(int v) {
    if (v < 0) return 0;
    if (v > 255) return 255;
    return (uint8_t)v;
}

class ScanlineRasterizer {
public:
    static void rasterize(const Gpu& gpu, const GpuVertex& v1, const GpuVertex& v2, const GpuVertex& v3, Screen* screen);
    static Color modulate_color(const Color& a, const Color& b)//my first try but tint where over all the texture colors
    {
        Color r;
        // (a*b)/255 for every rgb channel should be in module 255 (source: Stack Overflow mixed threads)
        r.r = (uint8_t)((int)a.r * (int)b.r / 255);
        r.g = (uint8_t)((int)a.g * (int)b.g / 255);
        r.b = (uint8_t)((int)a.b * (int)b.b / 255);
        r.a = (uint8_t)((int)a.a * (int)b.a / 255);
        return r;
    }
    static Color modulate_color_strength(const Color& tex, const Color& tint, float s) //second try with tint strenght factor  = s
    {
    s = std::clamp(s, 0.0f, 1.0f);

    // Convert in float (range 0..255)
    float tr = static_cast<float>(tex.r);
    float tg = static_cast<float>(tex.g);
    float tb = static_cast<float>(tex.b);

    float vr = static_cast<float>(tint.r);
    float vg = static_cast<float>(tint.g);
    float vb = static_cast<float>(tint.b);

    // fusing module coefficent function with strenght operator  => (tint/255)
    float fr = (1.0f - s) + s * (vr / 255.0f);
    float fg = (1.0f - s) + s * (vg / 255.0f);
    float fb = (1.0f - s) + s * (vb / 255.0f);

    Color out;
    out.r = to_u8(tr * fr);
    out.g = to_u8(tg * fg);
    out.b = to_u8(tb * fb);
    out.a = tex.a; // fix: same alpha of the original
    return out;

    }
};