#ifndef RESOURCEMANAGER_H
#define RESOURCEMANAGER_H

#include <gltexture.h>
#include <texturecache.h>
#include <string>

class ResourceManager
{
    private:
        static TextureCache textureCache;
    public:
        ResourceManager();
        ~ResourceManager();
        static GLTexture getTexture(std::string filePath);
};

#endif
