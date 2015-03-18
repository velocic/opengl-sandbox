#ifndef SPRITE_H
#define SPRITE_H

#include <GL/glew.h>

class Sprite
{
    private:
        float x;
        float y;
        float width;
        float height;
        GLuint vboID; //handle to the vertex buffer that holds our sprite on the GPU
    public:
        Sprite();
        ~Sprite();
        void init(float x, float y, float width, float height); //takes screen coordinates, then converts them to normalized device coordinates when displaying
        void draw();
};

#endif
