#ifndef TEXTURE_H
#define TEXTURE_H

#include <GL/glew.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <string>

class Texture
{
    private:
        SDL_Surface *texture;
        GLuint glTexture = 0;
    public:
        Texture(std::string texturePath);
        ~Texture();
        GLuint get();
        void createGLTexture();
        void unload();
};

#endif
