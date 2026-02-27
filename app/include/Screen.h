#pragma once
#include <raylib.h>
#include <vector>

class Screen 
{
public:
    Screen(int w, int h);
    ~Screen();
    void put_pixel(int x, int y, float z, Color color);
    void blit();
    void clear(Color color);

private:
    int _width;
    int _height;
    std::vector<Color> _color_buffer;
    std::vector<float> _depth_buffer;
    Texture2D _texture;
};