#include <texturecache.h>

TextureCache::TextureCache()
{
}

TextureCache::~TextureCache()
{
}

GLTexture TextureCache::getTexture(std::string filePath)
{
    auto iterator = textureMap.find(filePath);

    if (iterator == textureMap.end())
    {
        GLTexture newTexture = IOUtils::loadPNG(filePath);
        textureMap.insert(std::pair<std::string, GLTexture>(filePath, newTexture));
        return newTexture;
    }

    return iterator->second;
}
