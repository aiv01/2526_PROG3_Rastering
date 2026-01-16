#include "Screen.h"

Screen::Screen(int w, int h) 
    //: _width(w), _height(h)
{
    _width = w;
    _height = h;
    _color_buffer.resize(w * h);

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

void Screen::put_pixel(int x, int y, Color color) 
{
    if (x < 0 || x >= _width) return;
    if (y < 0 || y >= _height) return;

    _color_buffer[y * _width + x] = color;
}

void Screen::blit() 
{
    UpdateTexture(_texture, _color_buffer.data());
    DrawTexture(_texture, 0, 0, WHITE);
}

void Screen::clear() 
{
   std::fill(_color_buffer.begin(), _color_buffer.end(), BLACK);
}