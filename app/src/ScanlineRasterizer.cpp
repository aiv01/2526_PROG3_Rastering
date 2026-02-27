#include "ScanlineRasterizer.h"
#include <algorithm>
#include <array>
#include "raylib.h"
#include <stdint.h>
#include <iostream>

float interpolate_scalar(float a, float b, float gradient) 
{
    return a + gradient * (b - a);
}

Vector2f interpolate_vector2f(const Vector2f& a, const Vector2f& b, float gradient) 
{
    Vector2f result;
    result.x = interpolate_scalar(a.x, b.x, gradient);
    result.y = interpolate_scalar(a.y, b.y, gradient);
    return result;
}

Color interpolate_color(const Color& a, const Color& b, float gradient) 
{
    Color result;
    result.r = static_cast<uint8_t>(interpolate_scalar(a.r, b.r, gradient));
    result.g = static_cast<uint8_t>(interpolate_scalar(a.g, b.g, gradient));
    result.b = static_cast<uint8_t>(interpolate_scalar(a.b, b.b, gradient));
    result.a = static_cast<uint8_t>(interpolate_scalar(a.a, b.a, gradient));
    return result;
}

void rasterize_row(const Gpu& gpu, int y, 
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

    //int left_x = (int) ((float)left_edge_sp1.x + left_gradient_y * (float)(left_edge_sp2.x - left_edge_sp1.x));
    //int right_x = (int) ((float)right_edge_sp1.x + right_gradient_y * (float)(right_edge_sp2.x - right_edge_sp1.x));
    int left_x = interpolate_scalar(left_edge_sp1.x, left_edge_sp2.x, left_gradient_y);
    int right_x = interpolate_scalar(right_edge_sp1.x, right_edge_sp2.x, right_gradient_y);
    
    float left_z = interpolate_scalar(left_edge_v1.z_pos, left_edge_v2.z_pos, left_gradient_y);
    float right_z = interpolate_scalar(right_edge_v1.z_pos, right_edge_v2.z_pos, right_gradient_y);
    
    Color left_color;
    Color right_color;
    Vector2f left_uv;
    Vector2f right_uv;

    if (gpu.mode == GpuDrawMode::COLOR) {
        left_color = interpolate_color(left_edge_v1.color, left_edge_v2.color, left_gradient_y);
        right_color = interpolate_color(right_edge_v1.color, right_edge_v2.color, right_gradient_y);
    } else if (gpu.mode == GpuDrawMode::TEXTURE) {
        left_uv = interpolate_vector2f(left_edge_v1.uv, left_edge_v2.uv, left_gradient_y);
        right_uv = interpolate_vector2f(right_edge_v1.uv, right_edge_v2.uv, right_gradient_y);
    }

    for(int x = left_x; x <= right_x; ++x) {
        
        float gradient_x = 1.f;
        if (left_x < right_x) {
            gradient_x =  static_cast<float>(x - left_x) / static_cast<float>(right_x - left_x);
        }
        
        float sample_z = interpolate_scalar(left_z, right_z, gradient_x);

        Color sample_color;
        if (gpu.mode == GpuDrawMode::COLOR) {
            sample_color = interpolate_color(left_color, right_color, gradient_x);
        } else if (gpu.mode == GpuDrawMode::TEXTURE) { 
            Vector2f sample_uv = interpolate_vector2f(left_uv, right_uv, gradient_x);

            TextureCpu* texture = gpu.texture;
        
            //int text_x = (int) ((float)texture->width * sample_uv.x);
            //int text_y = (int) ((float)texture->height * sample_uv.y);
            int text_x = static_cast<int>(static_cast<float>(texture->width - 1) * sample_uv.x);
            int text_y = static_cast<int>(static_cast<float>(texture->height - 1) * (1.f - sample_uv.y));

            int text_index = (text_y * texture->width + text_x) * texture->pixel_size;

            sample_color.r = texture->pixels[text_index + 0];
            sample_color.g = texture->pixels[text_index + 1];
            sample_color.b = texture->pixels[text_index + 2];
            sample_color.a = texture->pixels[text_index + 3];
        }
        
        screen->put_pixel(x, y, sample_z, sample_color);
    }
}

void ScanlineRasterizer::rasterize(const Gpu& gpu, const GpuVertex& v1, const GpuVertex& v2, const GpuVertex& v3, Screen* screen) 
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
                rasterize_row(gpu, y, v1s,v2s, v1s,v3s, screen);
            } else {
                rasterize_row(gpu, y, v2s,v3s, v1s,v3s, screen);
            }
        }
    } else { // |>
        for(int y = p1s.y; y <= p3s.y; ++y) { 
            if (y < p2s.y) {
                rasterize_row(gpu, y, v1s,v3s, v1s,v2s, screen);
            } else {
                rasterize_row(gpu, y, v1s,v3s, v2s,v3s, screen);
            }
        }
    }
}

