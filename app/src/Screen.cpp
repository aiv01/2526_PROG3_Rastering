#include "Screen.h"
#include <limits>

Screen::Screen(int w, int h) 
    //: _width(w), _height(h)
{
    _width = w;
    _height = h;
    _color_buffer.resize(w * h);
    _depth_buffer.resize(w * h);

    Image img = {
        _color_buffer.data(),
        _width,
        _height,
        1,
        PIXELFORMAT_UNCOMPRESSED_R8G8B8A8
    };

    _texture = LoadTextureFromImage(img);
}

Screen::~Screen() 
{
    UnloadTexture(_texture);
}

void Screen::put_pixel(int x, int y, float z, Color color) 
{
    if (x < 0 || x >= _width) return;
    if (y < 0 || y >= _height) return;

    int index = y * _width + x;

    float prev_z = _depth_buffer[index];
    if (prev_z > z) return;
    
    _depth_buffer[index] = z;
    _color_buffer[index] = color;
}

void Screen::blit() 
{
    UpdateTexture(_texture, _color_buffer.data());
    DrawTexture(_texture, 0, 0, WHITE);
}

void Screen::clear(Color color) 
{
   std::fill(_color_buffer.begin(), _color_buffer.end(), color);
   std::fill(_depth_buffer.begin(), _depth_buffer.end(), std::numeric_limits<float>().lowest());
}