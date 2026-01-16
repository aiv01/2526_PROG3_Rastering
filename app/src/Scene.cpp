#include "Scene.h"
#include <raylib.h>
#include "LineRaster.h"

Scene::Scene(int w, int h) 
{ 
    _screen = new Screen(w, h);
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
    
    dda_line_raster((int)x1, (int)y1, (int)x2, (int)y2, RED, _screen);

    _screen->blit();
}

void Scene::Destroy() 
{ 
    delete _screen;
}

