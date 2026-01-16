#include "Maths.h"
#include <algorithm>

namespace Maths {

    int min3(int a, int b, int c) 
    {
        return std::min(std::min(a, b), c);
    }

    int max3(int a, int b, int c) 
    {
        return std::max(std::max(a, b), c);
    }

    float det(Vector2i p, Vector2i v1, Vector2i v2) {
        //V1 -> V2
        int vx = v2.x - v1.x;
        int vy = v2.y - v1.y;

        //V1 -> P
        int px = p.x - v1.x;
        int py = p.y - v1.y;

        return vx * py - vy * px;
    }

}