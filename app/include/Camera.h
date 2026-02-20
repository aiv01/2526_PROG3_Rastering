#pragma once

#include "Maths.h" 

class ACamera {
public:
    virtual Vector2i worldToScreenSpace(Vector3f worldPoint) = 0;
    virtual Vector3f worldToCameraSpace(Vector3f worldPoint) = 0;
    virtual ~ACamera() = default;
};

class PerspectiveCamera : public ACamera {
public:
    PerspectiveCamera(int screenWidth, int screenHeight, float fovDegrees);
    Vector2i worldToScreenSpace(Vector3f worldPoint) override;
    Vector3f worldToCameraSpace(Vector3f worldPoint) override;
private:
    int _screenHeight;
    int _screenWidth;
    
    Vector3f _position;
    float _aspectRatio;
    float _fov;

    //float nearClip;
    //float farClip;
};

class OrthographicCamera : public ACamera {
public:
    OrthographicCamera(int screenWidth, int screenHeight, float ortoSize);
    Vector2i worldToScreenSpace(Vector3f worldPoint) override;
    Vector3f worldToCameraSpace(Vector3f worldPoint) override;
private:
    int _screenHeight;
    int _screenWidth;
    
    Vector3f _position;
    float _aspectRatio;
    float _orthoSize;
};