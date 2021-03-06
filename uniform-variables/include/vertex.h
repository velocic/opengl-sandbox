#ifndef VERTEX_H
#define VERTEX_H

#include <GL/glew.h>
//Note: Vertex data should be a multiple of 4 bytes
struct Vertex
{
    struct Position {
        float x;
        float y;
    } position;

    struct Color {
        GLubyte r;
        GLubyte g;
        GLubyte b;
        GLubyte a;
    } color;
};

#endif
