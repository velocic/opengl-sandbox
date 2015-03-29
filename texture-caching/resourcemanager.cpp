#include <resourcemanager.h>

TextureCache ResourceManager::textureCache;

ResourceManager::ResourceManager()
{
}

ResourceManager::~ResourceManager()
{
}

GLTexture ResourceManager::getTexture(std::string filePath)
{
    return textureCache.getTexture(filePath);
}
