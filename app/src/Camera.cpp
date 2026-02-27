#include "Camera.h"
#include <math.h>
#include "Maths.h"

PerspectiveCamera::PerspectiveCamera(int screenWidth, int screenHeight, float fovDegrees) 
    : _screenWidth(screenWidth), _screenHeight(screenHeight), _fov(fovDegrees), _position({0, 0, 0})
{
    _aspectRatio = (float)screenWidth / (float)screenHeight;
}

Vector3f PerspectiveCamera::getPosition() const {
    return _position;
}

Vector2i PerspectiveCamera::worldToScreenSpace(Vector3f worldPoint) {
    Vector3f cameraPoint = worldToCameraSpace(worldPoint);

    float planeX = cameraPoint.x / -cameraPoint.z;
    float planeY = cameraPoint.y / -cameraPoint.z;
    
    float halfFovDegrees = _fov * 0.5f;
    float halfFovRadians = halfFovDegrees * Maths::PI2 / 180.f;
    float tanFov = tanf(halfFovRadians);

    planeX /= tanFov;
    planeY /= tanFov;

    planeX /= _aspectRatio;

    // Plane {-1, 1} to Screen {w, h}
    int screenX = (int)( (planeX + 1.f) * 0.5f * (float)_screenWidth);
    int screenY = (int)( (1.f - (planeY + 1.f) * 0.5f) * (float)_screenHeight);

    return {screenX, screenY};
}

Vector3f PerspectiveCamera::worldToCameraSpace(Vector3f worldPoint) {
    Vector3f cameraPoint = worldPoint - _position;
    return cameraPoint;
}

bool PerspectiveCamera::isFaceCulled(const Vector3f& cp1, const Vector3f& cp2, const Vector3f& cp3) const {
    Vector3f v12 = cp2 - cp1;
    Vector3f v13 = cp3 - cp1;

    Vector3f face_normal = v12.cross(v13);
    Vector3f cp1_to_camera = cp1 * -1.f;

    float dot = cp1_to_camera.dot(face_normal);
    if (dot >= 0) return false; // visible
    return true;
}

OrthographicCamera::OrthographicCamera(int screenWidth, int screenHeight, float orthoSize) 
    : _screenWidth(screenWidth), _screenHeight(screenHeight), _orthoSize(orthoSize), _position({0, 0, 0})
{
    _aspectRatio = (float)screenWidth / (float)screenHeight;
}

Vector3f OrthographicCamera::getPosition() const {
    return _position;
}

Vector2i OrthographicCamera::worldToScreenSpace(Vector3f worldPoint) {
    Vector3f cameraPoint = worldToCameraSpace(worldPoint);

    float planeX = cameraPoint.x / _orthoSize;
    float planeY = cameraPoint.y / _orthoSize;
    
    planeX /= _aspectRatio;

    // Plane {-1, 1} to Screen {w, h}
    int screenX = (int)( (planeX + 1.f) * 0.5f * (float)_screenWidth);
    int screenY = (int)( (1.f - (planeY + 1.f) * 0.5f) * (float)_screenHeight);

    return {screenX, screenY};
}

Vector3f OrthographicCamera::worldToCameraSpace(Vector3f worldPoint) {
    Vector3f cameraPoint = worldPoint - _position;
    return cameraPoint;
}

bool OrthographicCamera::isFaceCulled(const Vector3f& cp1, const Vector3f& cp2, const Vector3f& cp3) const {
    Vector3f v12 = cp2 - cp1;
    Vector3f v13 = cp3 - cp1;

    Vector3f face_normal = v12.cross(v13);
    Vector3f cp1_to_camera = cp1 * -1.f;

    float dot = cp1_to_camera.dot(face_normal);
    if (dot >= 0) return false; // visible
    return true;
}