#pragma once

struct Vector2i {
    int x;
    int y;
};

namespace Maths {

    /// @brief Get the min value among the 3 values.
    int min3(int a, int b, int c);
    /// @brief Get the max value among the 3 values.
    int max3(int a, int b, int c);
    float det(Vector2i p, Vector2i v1, Vector2i v2);
}
