#ifndef TEXTURECACHE_H
#define TEXTURECACHE_H

#include <map>
#include <string>
#include <utility>
#include <gltexture.h>
#include <ioutils.h>

class TextureCache
{
    private:
        std::map<std::string, GLTexture> textureMap;
    public:
        TextureCache();
        ~TextureCache();
        GLTexture getTexture(std::string filePath);
};

#endif
