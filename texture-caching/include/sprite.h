#ifndef SPRITE_H
#define SPRITE_H

#include <gltexture.h>
#include <GL/gl3w.h>
#include <resourcemanager.h>
#include <string>

class Sprite
{
    private:
        float x;
        float y;
        float width;
        float height;
        GLuint vboID; //handle to the vertex buffer that holds our sprite on the GPU
        GLTexture texture;
    public:
        Sprite();
        ~Sprite();
        void init(float x, float y, float width, float height, std::string texturePath); //takes screen coordinates, then converts them to normalized device coordinates when displaying
        void draw();
};

#endif
