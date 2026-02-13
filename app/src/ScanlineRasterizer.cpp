#include "ScanlineRasterizer.h"
#include <algorithm>
#include <array>
#include "raylib.h"

void rasterize_row(int y, 
                   const Vector2i& left_edge_v1, const Vector2i& left_edge_v2,
                   const Vector2i& right_edge_v1, const Vector2i& right_edge_v2,
                   const Color& color,
                   Screen* screen) 
{
    float left_gradient_y = 1.f;
    if (left_edge_v2.y != left_edge_v1.y) {
        left_gradient_y =  float(y - left_edge_v1.y) / (float)(left_edge_v2.y - left_edge_v1.y);
    }

    float right_gradient_y = 1.f;
    if (right_edge_v2.y != right_edge_v1.y) {
        right_gradient_y =  float(y - right_edge_v1.y) / (float)(right_edge_v2.y - right_edge_v1.y);
    }

    int left_x = (int) ((float)left_edge_v1.x + left_gradient_y * (float)(left_edge_v2.x - left_edge_v1.x));
    int right_x = (int) ((float)right_edge_v1.x + right_gradient_y * (float)(right_edge_v2.x - right_edge_v1.x));

    for(int x = left_x; x <= right_x; ++x) {
        screen->put_pixel(x, y, color);
    }
}


void ScanlineRasterizer::rasterize(const Vector2i& p1, const Vector2i& p2, const Vector2i& p3, const Color& color, Screen* screen) 
{
    std::array<std::reference_wrapper<const Vector2i>, 3> points = {p1, p2, p3};
    std::sort(points.begin(), points.end(), [](const Vector2i& p1, const Vector2i& p2) {
        return p1.y < p2.y;
    });

    auto& p1s = points[0].get();
    auto& p2s = points[1].get();
    auto& p3s = points[2].get();

    //Mi=X/Y 

    float inv_slope_p1p2 = (float)(p2s.x - p1s.x) / (float)(p2s.y - p1s.y);
    float inv_slope_p1p3 = (float)(p3s.x - p1s.x) / (float)(p3s.y - p1s.y);

    // <|
    if (inv_slope_p1p2 < inv_slope_p1p3) {
        for(int y = p1s.y; y <= p3s.y; ++y) {
            if (y < p2s.y) {
                rasterize_row(y, p1s,p2s, p1s,p3s, color, screen);
            } else {
                rasterize_row(y, p2s,p3s, p1s,p3s, color, screen);
            }
        }
    } else { // |>
        for(int y = p1s.y; y <= p3s.y; ++y) { 
            if (y < p2s.y) {
                rasterize_row(y, p1s,p3s, p1s,p2s, color, screen);
            } else {
                rasterize_row(y, p1s,p3s, p2s,p3s, color, screen);
            }
        }
    }
}

