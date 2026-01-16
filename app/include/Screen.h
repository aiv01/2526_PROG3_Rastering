#pragma once
#include <raylib.h>
#include <vector>

class Screen 
{
public:
    Screen(int w, int h);
    ~Screen();
    void put_pixel(int x, int y, Color color);
    void blit();
    void clear();

private:
    int _width;
    int _height;
    std::vector<Color> _color_buffer;
    Texture2D _texture;
};