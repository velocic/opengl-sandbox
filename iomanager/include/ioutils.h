#ifndef IOUTILS_H
#define IOUTILS_H

#include <vector>
#include <fstream>
#include <iostream>
#include <gltexture.h>

namespace IOUtils
{
    bool readFileToBuffer(std::string filePath, std::vector<char> &buffer);
    //decodePNG is contained in lodepng.cpp, and is third-party. See that file for license info
    int decodePNG(std::vector<unsigned char>& out_image, unsigned long& image_width, unsigned long& image_height, const unsigned char* in_png, size_t in_size, bool convert_to_rgba32 = true);
    GLTexture IOUtils::loadPNG(std::string filePath)
}

#endif
