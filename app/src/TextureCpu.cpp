#include "TextureCpu.h"
#include <raylib.h>
#include <iostream>

TextureCpu* TextureCpu::load_from_file(const std::string& file_path) 
{
    Image img = LoadImage(file_path.c_str());
    if (!IsImageValid(img)) {
        std::cout << "Error loading image: " << file_path << "\n";
        return nullptr;
    }

    ImageFormat(&img, PIXELFORMAT_UNCOMPRESSED_R8G8B8A8);

    int width = img.width;
    int height = img.height;
    int byte_per_pixel = 4;
    size_t size = static_cast<size_t>(width * height * byte_per_pixel);
    uint8_t* data = reinterpret_cast<uint8_t*>(img.data);

    std::vector<uint8_t> pixels(data, data + size);

    auto* t = new TextureCpu(width, height, byte_per_pixel, pixels);
    UnloadImage(img);
    return t;
}

TextureCpu::TextureCpu(int w, int h, int psize, std::vector<uint8_t> pxs) 
    : width(w), height(h), pixel_size(psize), pixels(pxs)
{ }