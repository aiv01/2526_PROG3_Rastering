#pragma once
#include "Screen.h"
class Scene {
public:
    Scene(int w, int h);
    void Update(float delta_time);
    void Destroy();
    Screen* _screen;
};