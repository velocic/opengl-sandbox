#include <sprite.h>

Sprite::Sprite()
{
    vboID = 0;
}

Sprite::~Sprite()
{
    if (vboID != 0) {
        glDeleteBuffers(1, &vboID);
    }
}

void Sprite::init(float x, float y, float width, float height)
{
    this->x = x;
    this->y = y;
    this->width = width;
    this->height = height;

    if (vboID == 0) {
        //give us 1 buffer, and a handle to it which will be stored in vboID
        glGenBuffers(1, &vboID);
    }

    //create a square from 2 triangles. needs 6 vertices (2 triangles x 3 vertices each) that are 2 dimentional
    //so we need an array of (2 x 3 x 2) elements to hold the vertex data. from the tutorial, the origin point seems to be
    //the bottom-left corner of the screen
    float vertexData[12] = {
        //x, y
        //triangle 1
        x + width, y + height,
        x, y + height,
        x, y,
        //triangle 2
        x, y,
        x + width, y,
        x + width, y + height
    };

    glBindBuffer(GL_ARRAY_BUFFER, vboID);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertexData), vertexData, GL_STATIC_DRAW);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void Sprite::draw()
{
    glBindBuffer(GL_ARRAY_BUFFER, vboID);

    glEnableVertexAttribArray(0);

    //point GL to the start of our data
    //0th attrib array index, each piece of data has 2 pieces, the type of the data, don't normalize the data
    //no stride, since our data begins at the beginning of the array (i.e. not interleaved), and point to the beginning of
    //the data (since it is not interleaved)
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, 0);

    //draw triangles, starting at the beginning of the array. draw 6 vertices
    glDrawArrays(GL_TRIANGLES, 0, 6);
    
    glDisableVertexAttribArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}
