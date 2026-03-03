#pragma once
#include "Screen.h"
#include "Camera.h"
#include "ObjParser.h"
#include "TextureCpu.h"


static bool is_triangle_offscreen(const Vector2i& p1, const Vector2i& p2, const Vector2i& p3,
                                  int w, int h)
{
    //all vertex out from left
    if (p1.x < 0 && p2.x < 0 && p3.x < 0) return true;
    //all vertex out from right
    if (p1.x >= w && p2.x >= w && p3.x >= w) return true;
    // all vertex out from up
    if (p1.y < 0 && p2.y < 0 && p3.y < 0) return true;
    // all vertex out from down
    if (p1.y >= h && p2.y >= h && p3.y >= h) return true;

    return false;
}


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