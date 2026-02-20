#include "ScanlineRasterizer.h"
#include <algorithm>
#include <array>
#include "raylib.h"
#include <stdint.h>

float interpolate_scalar(float a, float b, float gradient) 
{
    return a + gradient * (b - a);
}

Color interpolate_color(const Color& a, const Color& b, float gradient) 
{
    Color result;
    result.r = (uint8_t)( (float)a.r + gradient * (float)(b.r - a.r) );
    result.g = (uint8_t)( (float)a.g + gradient * (float)(b.g - a.g) );
    result.b = (uint8_t)( (float)a.b + gradient * (float)(b.b - a.b) );
    result.a = (uint8_t)( (float)a.a + gradient * (float)(b.a - a.a) );
    return result;
}

void rasterize_row(int y, 
                   const GpuVertex& left_edge_v1, const GpuVertex& left_edge_v2,
                   const GpuVertex& right_edge_v1, const GpuVertex& right_edge_v2,
                   Screen* screen) 
{
    const Vector2i& left_edge_sp1 = left_edge_v1.screen_pos;
    const Vector2i& left_edge_sp2 = left_edge_v2.screen_pos;
    const Vector2i& right_edge_sp1 = right_edge_v1.screen_pos;
    const Vector2i& right_edge_sp2 = right_edge_v2.screen_pos;

    float left_gradient_y = 1.f;
    if (left_edge_sp2.y != left_edge_sp1.y) {
        left_gradient_y =  float(y - left_edge_sp1.y) / (float)(left_edge_sp2.y - left_edge_sp1.y);
    }

    float right_gradient_y = 1.f;
    if (right_edge_sp2.y != right_edge_sp1.y) {
        right_gradient_y =  float(y - right_edge_sp1.y) / (float)(right_edge_sp2.y - right_edge_sp1.y);
    }

    int left_x = (int) ((float)left_edge_sp1.x + left_gradient_y * (float)(left_edge_sp2.x - left_edge_sp1.x));
    int right_x = (int) ((float)right_edge_sp1.x + right_gradient_y * (float)(right_edge_sp2.x - right_edge_sp1.x));

    Color left_color = interpolate_color(left_edge_v1.color, left_edge_v2.color, left_gradient_y);
    Color right_color = interpolate_color(right_edge_v1.color, right_edge_v2.color, right_gradient_y);

    float left_z = interpolate_scalar(left_edge_v1.z_pos, left_edge_v2.z_pos, left_gradient_y);
    float right_z = interpolate_scalar(right_edge_v1.z_pos, right_edge_v2.z_pos, right_gradient_y);

    for(int x = left_x; x <= right_x; ++x) {
        
        float gradient_x = 1.f;
        if (left_x < right_x) {
            gradient_x =  static_cast<float>(x - left_x) / static_cast<float>(right_x - left_x);
        }

        Color sample_color = interpolate_color(left_color, right_color, gradient_x);
        float sample_z = interpolate_scalar(left_z, right_z, gradient_x);

        screen->put_pixel(x, y, sample_z, sample_color);
    }
}


void ScanlineRasterizer::rasterize(const GpuVertex& v1, const GpuVertex& v2, const GpuVertex& v3, Screen* screen) 
{
    std::array<std::reference_wrapper<const GpuVertex>, 3> points = {v1, v2, v3};
    std::sort(points.begin(), points.end(), [](const GpuVertex& p1, const GpuVertex& p2) {
        return p1.screen_pos.y < p2.screen_pos.y;
    });

    auto& v1s = points[0].get();
    auto& v2s = points[1].get();
    auto& v3s = points[2].get();

    auto& p1s = v1s.screen_pos;
    auto& p2s = v2s.screen_pos;
    auto& p3s = v3s.screen_pos;

    //Mi=X/Y 

    float inv_slope_p1p2 = (float)(p2s.x - p1s.x) / (float)(p2s.y - p1s.y);
    float inv_slope_p1p3 = (float)(p3s.x - p1s.x) / (float)(p3s.y - p1s.y);

    // <|
    if (inv_slope_p1p2 < inv_slope_p1p3) {
        for(int y = p1s.y; y <= p3s.y; ++y) {
            if (y < p2s.y) {
                rasterize_row(y, v1s,v2s, v1s,v3s, screen);
            } else {
                rasterize_row(y, v2s,v3s, v1s,v3s, screen);
            }
        }
    } else { // |>
        for(int y = p1s.y; y <= p3s.y; ++y) { 
            if (y < p2s.y) {
                rasterize_row(y, v1s,v3s, v1s,v2s, screen);
            } else {
                rasterize_row(y, v1s,v3s, v2s,v3s, screen);
            }
        }
    }
}

