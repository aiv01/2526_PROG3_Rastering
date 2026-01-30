#include "Scene.h"
#include <raylib.h>
#include "Maths.h"
#include "ShapeRasterizer.h"

Scene::Scene(int w, int h) 
{ 
    _screen = new Screen(w, h);
    _camera = new PerspectiveCamera(w, h, 60.f);
}

void Scene::Update(float delta_time) 
{ 
    //dda_line_raster(100, 400, 400, 200, RED);
    _screen->clear();

    static float x1 = 50;
    static float y1 = 50;
    static float x2 = 200;
    static float y2 = 250;

    float speed = 10;
    x1 += (speed * delta_time);
    y1 += (speed * delta_time);
    
    x2 += (speed * delta_time);
    y2 += (speed * delta_time);
    
    ShapeRasterizer::dda_line_raster((int)0, (int)0, (int)x2, (int)y2, RED, _screen);

    // triangle by 3 edges
    ShapeRasterizer::dda_line_raster(50, 200, 150, 200, GREEN, _screen);
    ShapeRasterizer::dda_line_raster(50, 200, 100, 50, GREEN, _screen);
    ShapeRasterizer::dda_line_raster(150, 200, 100, 50, GREEN, _screen);

    // triangle with bbox
    ShapeRasterizer::bbox_triangle_raster({50, 200}, {150, 200}, {100, 50}, BLUE, _screen);

    // Triangle in WorldSpace
    Vector3f wp1{0.f, 0.f, -10.f};
    Vector3f wp2{-2.f, -2.f, -10.f};
    Vector3f wp3{ 2.f, -2.f, -10.f};

    Vector2i sp1 = _camera->worldToScreenSpace(wp1);
    Vector2i sp2 = _camera->worldToScreenSpace(wp2);
    Vector2i sp3 = _camera->worldToScreenSpace(wp3);

    ShapeRasterizer::bbox_triangle_raster(sp1, sp2, sp3, RED, _screen);

    _screen->blit();
}

void Scene::Destroy() 
{ 
    delete _screen;
    delete _camera;
}

