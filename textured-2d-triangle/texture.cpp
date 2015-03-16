#include <texture.h>

Texture::Texture(std::string texturePath)
{
    texture = IMG_Load(texturePath.c_str());
}

Texture::~Texture()
{
    unload();
}

GLuint Texture::get()
{
    return glTexture;
}

void Texture::createGLTexture()
{
    glGenTextures(1, &glTexture);
    glBindTexture(GL_TEXTURE_2D, glTexture);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexImage2D(
        GL_TEXTURE_2D,
        0,
        GL_RGBA,
        (GLsizei)texture->w,
        (GLsizei)texture->h,
        0,
        GL_RGBA,
        GL_UNSIGNED_BYTE,
        texture->pixels
    );
    glBindTexture(GL_TEXTURE_2D, 0);
}

void Texture::unload()
{
    SDL_FreeSurface(texture);
    glDeleteTextures(1, &glTexture);
    glTexture = 0;
}
