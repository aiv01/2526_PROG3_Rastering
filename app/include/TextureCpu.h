#pragma once
#include <string>
#include <vector>
#include <stdint.h>

class TextureCpu {
public:
    static TextureCpu* load_from_file(const std::string& file_path);
    TextureCpu(int width, int height, int pixel_size, std::vector<uint8_t> pixels);
public:
    int width;
    int height;
    int pixel_size;
    std::vector<uint8_t> pixels;
};