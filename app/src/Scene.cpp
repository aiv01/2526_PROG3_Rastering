#include "Scene.h"
#include <raylib.h>
#include "Maths.h"
#include "ShapeRasterizer.h"
#include "ObjParser.h"

Scene::Scene(int w, int h) 
{ 
    _screen = new Screen(w, h);
    _camera = new PerspectiveCamera(w, h, 60.f);
    //_camera = new OrthographicCamera(w, h, 5.f);

    ObjParser::TryParse("resources/quad.obj", _quad);
    ObjParser::TryParse("resources/suzanne.obj", _suzanne);
}

void draw_quad(Obj& obj, ACamera* camera, Screen* screen) {
    for(int i=0; i < obj.triangles.size(); ++i) {
        auto& triangle = obj.triangles[i];

        //reinterpret_cast
        Vector3f mp1 = *(Vector3f*)&(triangle.v1.point);
        Vector3f mp2 = *(Vector3f*)&(triangle.v2.point);
        Vector3f mp3 = *(Vector3f*)&(triangle.v3.point);

        Vector3f wp1 = mp1 - Vector3f{0, 0, 4};
        Vector3f wp2 = mp2 - Vector3f{0, 0, 4};
        Vector3f wp3 = mp3 - Vector3f{0, 0, 4};
        
        Vector2i sp1 = camera->worldToScreenSpace(wp1);
        Vector2i sp2 = camera->worldToScreenSpace(wp2);
        Vector2i sp3 = camera->worldToScreenSpace(wp3);

        ShapeRasterizer::bbox_triangle_raster(sp1, sp2, sp3, GREEN, screen);
    }
}

void draw_suzanne(Obj& obj, bool wireframe, float deltaTime, ACamera* camera, Screen* screen) {
    static float rotation = 0.f;
    rotation += 10.f * deltaTime;
    
    for(int i=0; i < obj.triangles.size(); ++i) {
        auto& triangle = obj.triangles[i];

        Vector3f mp1 = *(Vector3f*)&(triangle.v1.point);
        Vector3f mp2 = *(Vector3f*)&(triangle.v2.point);
        Vector3f mp3 = *(Vector3f*)&(triangle.v3.point);
        
        // Scale -> Rotate -> Translate
        Vector3f wp1 = mp1 * 2.f;
        Vector3f wp2 = mp2 * 2.f;
        Vector3f wp3 = mp3 * 2.f;

        wp1 = wp1.rotate_y(rotation);
        wp2 = wp2.rotate_y(rotation);
        wp3 = wp3.rotate_y(rotation);

        wp1 = wp1 - Vector3f{0, 0, 5};
        wp2 = wp2 - Vector3f{0, 0, 5};
        wp3 = wp3 - Vector3f{0, 0, 5};
        
        Vector2i sp1 = camera->worldToScreenSpace(wp1);
        Vector2i sp2 = camera->worldToScreenSpace(wp2);
        Vector2i sp3 = camera->worldToScreenSpace(wp3);

        if (wireframe) {
            ShapeRasterizer::dda_line_raster(sp1.x, sp1.y, sp2.x, sp2.y, GREEN, screen);
            ShapeRasterizer::dda_line_raster(sp1.x, sp1.y, sp3.x, sp3.y, GREEN, screen);
            ShapeRasterizer::dda_line_raster(sp2.x, sp2.y, sp3.x, sp3.y, GREEN, screen);
        } else {
            ShapeRasterizer::bbox_triangle_raster(sp1, sp2, sp3, GREEN, screen);
        }
    }
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

    //draw_quad(_quad, _camera, _screen);

    draw_suzanne(_suzanne, true, delta_time, _camera, _screen);

    _screen->blit();
}

void Scene::Destroy() 
{ 
    delete _screen;
    delete _camera;
}

