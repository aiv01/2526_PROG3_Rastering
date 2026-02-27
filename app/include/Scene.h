#pragma once
#include "Screen.h"
#include "Camera.h"
#include "ObjParser.h"
#include "TextureCpu.h"

class Scene {
public:
    Scene(int w, int h);
    void Update(float delta_time);
    void Destroy();
    Screen* _screen;
    ACamera* _camera;

    Obj _quad;
    Obj _suzanne;
    Obj _trup;

    TextureCpu* _smile_texture;
    TextureCpu* _trup_texture;
};