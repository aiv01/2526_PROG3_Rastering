#include "Camera.h"
#include <math.h>
#include "Maths.h"

PerspectiveCamera::PerspectiveCamera(int screenWidth, int screenHeight, float fovDegrees) 
    : _screenWidth(screenWidth), _screenHeight(screenHeight), _fov(fovDegrees), _position({0, 0, 0})
{
    _aspectRatio = (float)screenWidth / (float)screenHeight;
}

Vector2i PerspectiveCamera::worldToScreenSpace(Vector3f worldPoint) {
    Vector3f cameraPoint = worldPoint - _position;

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


OrthographicCamera::OrthographicCamera(int screenWidth, int screenHeight, float orthoSize) 
    : _screenWidth(screenWidth), _screenHeight(screenHeight), _orthoSize(orthoSize), _position({0, 0, 0})
{
    _aspectRatio = (float)screenWidth / (float)screenHeight;
}

Vector2i OrthographicCamera::worldToScreenSpace(Vector3f worldPoint) {
    Vector3f cameraPoint = worldPoint - _position;

    float planeX = cameraPoint.x / _orthoSize;
    float planeY = cameraPoint.y / _orthoSize;
    
    planeX /= _aspectRatio;

    // Plane {-1, 1} to Screen {w, h}
    int screenX = (int)( (planeX + 1.f) * 0.5f * (float)_screenWidth);
    int screenY = (int)( (1.f - (planeY + 1.f) * 0.5f) * (float)_screenHeight);

    return {screenX, screenY};
}