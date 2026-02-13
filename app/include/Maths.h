#pragma once

struct Vector2i {
    int x;
    int y;
};

struct Vector3f {
    float x;
    float y;
    float z;

    Vector3f operator-(const Vector3f& other) const;
    Vector3f operator*(float scalar) const;
    Vector3f rotate_y(float angleDegrees) const;
};

namespace Maths {

    const float PI2 = 3.1415926f;

    /// @brief Get the min value among the 3 values.
    int min3(int a, int b, int c);
    /// @brief Get the max value among the 3 values.
    int max3(int a, int b, int c);
    float det(Vector2i p, Vector2i v1, Vector2i v2);
}
