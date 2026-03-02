#pragma once
#include <stdint.h>
#include <cmath>
#include <algorithm>

struct Vector2i {
    int x;
    int y;
};

struct Vector2f {
    float x;
    float y;
};

struct Vector3f {
    float x;
    float y;
    float z;

    Vector3f operator-(const Vector3f& other) const;
    Vector3f operator*(float scalar) const;
    Vector3f rotate_y(float angleDegrees) const;

    void normalize();
    float magnitude();
    float dot(const Vector3f& other) const;

    Vector3f reflect(const Vector3f& norm) const;
    Vector3f cross(const Vector3f& other) const;
};
/*
struct XColor {
    uint8_t r;
    uint8_t g;
    uint8_t b;
    uint8_t a;

    XColor operator*(float scalar) const;
    XColor operator+(const XColor& color) const;
};*/
struct XColor {
    float r;
    float g;
    float b;
    float a;

    XColor operator*(float scalar) const;
    XColor operator+(const XColor& color) const;
};

// my cast and clamp function (inline return type to avoid multiple definition error : done at lesson with Prof Fattori)
inline uint8_t to_u8(float v) {
    v = std::clamp(v, 0.0f, 255.0f);
    return static_cast<uint8_t>(v + 0.5f);
}

namespace Maths {

    const float PI2 = 3.1415926f;

    /// @brief Get the min value among the 3 values.
    int min3(int a, int b, int c);
    /// @brief Get the max value among the 3 values.
    int max3(int a, int b, int c);
    float det(Vector2i p, Vector2i v1, Vector2i v2);
}
