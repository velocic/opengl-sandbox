#ifndef BMPLOADER_H
#define BMPLOADER_H

#include <GL/gl3w.h>
#include <string>
#include <vector>
#include <fstream>
#include <iterator>
#include <iostream>

namespace BMPLoader
{
    GLuint loadBMP_custom(std::string imagePath);
}

#endif
