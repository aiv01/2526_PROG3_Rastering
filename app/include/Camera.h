#pragma once

#include "Maths.h" 

class PerspectiveCamera {

public:
    PerspectiveCamera(int screenWidth, int screenHeight, float fovDegrees);
    Vector2i worldToScreenSpace(Vector3f worldPoint);
private:
    int _screenHeight;
    int _screenWidth;
    
    Vector3f _position;

    float _fov;
    float _aspectRatio;
    //float nearClip;
    //float farClip;
};