#ifndef IMAGELOADER_H
#define IMAGELOADER_H

#include <gl/glew.h>
#include <gltexture.h>
#include <ioutils.h>

namespace ImageLoader
{
    GLTexture loadPNG(std::string filePath);
}

#endif
