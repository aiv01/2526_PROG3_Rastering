#include "Maths.h"
#include <algorithm>
#include <math.h>

Vector3f Vector3f::operator-(const Vector3f& other) const {
    return {x - other.x, y - other.y, z - other.z};
}

Vector3f Vector3f::operator*(float scalar) const {
    return {x * scalar, y * scalar, z * scalar};
}

Vector3f Vector3f::rotate_y(float angleDegrees) const {
    float rads = angleDegrees * Maths::PI2 / 180.f;

    Vector3f result;
    result.x = cosf(rads) * x - sinf(rads) * z;
    result.y = y;
    result.z = sinf(rads) * x + cosf(rads) * z;
    return result;
}

void Vector3f::normalize() {
    float magn = magnitude();
    x /= magn;
    y /= magn;
    z /= magn;
}

float Vector3f::magnitude() {
    //return sqrtf( x * x + y * y + z * z );
    return sqrtf( dot(*this) );
}

float Vector3f::dot(const Vector3f& other) const {
    return x * other.x + y * other.y + z * other.z;
}

Vector3f Vector3f::reflect(const Vector3f& norm) const {
    // R = I - 2 * dot(I,N) * N;
    return *this - norm * (2.f * dot(norm));
}

Vector3f Vector3f::cross(const Vector3f& other) const {
    Vector3f r;
    r.x = y * other.z - z * other.y;
    r.y = z * other.x - x * other.z;
    r.z = x * other.y - y * other.x;
    return r;
}

XColor XColor::operator*(float scalar) const {
    XColor c;
    c.r = static_cast<uint8_t>(static_cast<float>(r) * scalar);
    c.g = static_cast<uint8_t>(static_cast<float>(g) * scalar);
    c.b = static_cast<uint8_t>(static_cast<float>(b) * scalar);
    c.a = static_cast<uint8_t>(static_cast<float>(a) * scalar);
    return c;
}

XColor XColor::operator+(const XColor& color) const {
    XColor c;
    c.r = r + color.r;
    c.g = g + color.g;
    c.b = b + color.b;
    c.a = a + color.a;
    return c;
}

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