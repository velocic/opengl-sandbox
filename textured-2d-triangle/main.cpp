#include <GL/glew.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <shader.h>
#include <programlinker.h>
#include <iostream>
#include <window.h>
#include <texture.h>
#include <glm/glm.hpp>
#include <vector>

GLuint vertexBufferObject;
GLuint vertexArrayObject;

int main()
{
    //Start SDL
    SDL_Init(SDL_INIT_VIDEO | SDL_INIT_EVENTS);
    IMG_Init(IMG_INIT_PNG);

    Window window(640, 480);
    Texture texture("hazard.png");
    texture.createGLTexture();



    //load shaders & link them
    Shader vertex(GL_VERTEX_SHADER, "shaders/vertex.glsl");
    Shader fragment(GL_FRAGMENT_SHADER, "shaders/fragment.glsl");
    std::vector<Shader> shaders = {vertex, fragment};
    ProgramLinker program(shaders);
    program.link();

    std::cout << "got past program link" << std::endl;

    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, texture.get());
    
    //wat. need to understand what is going on here
    GLuint texLocation = glGetUniformLocation(program.getProgram(), "tex");
    glUniform1i(texLocation, 0);

    //put the three triangle vertices, and the texture coordinates into the VBO
    GLfloat vertexData[] = {
        //x, y, z, u, v
        0.0f, 0.8f, 0.0f, 0.5f, 1.0f,
        -0.8f, -0.8f, 0.0f, 0.0f, 0.0f,
        0.8f, -0.8f, 0.0f, 1.0f, 0.0f
    };

    //create and bind a vertex array object
    glGenVertexArrays(1, &vertexArrayObject);
    glBindVertexArray(vertexArrayObject);

    //create and bind a vertex buffer object
    glGenBuffers(1, &vertexBufferObject);
    glBindBuffer(GL_ARRAY_BUFFER, vertexBufferObject);

    //connect xyz to the "vert" attribute of the vertex shader
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertexData), vertexData, GL_STATIC_DRAW);
    GLint attrib = glGetAttribLocation(program.getProgram(), "vert");
    glEnableVertexAttribArray(attrib);
    glVertexAttribPointer(attrib, 3, GL_FLOAT, GL_FALSE, 5*sizeof(GLfloat), NULL);
    //end connecting vert

    //connect the uv coordinates to the "vertTexCoord" attribute of the vertex shader
    GLint vertTexCoord = glGetAttribLocation(program.getProgram(), "vertTexCoord");
    glEnableVertexAttribArray(vertTexCoord);
    glVertexAttribPointer(vertTexCoord, 2, GL_FLOAT, GL_TRUE, 5*sizeof(GLfloat), (const GLvoid *)(3 * sizeof(GLfloat)));
    //end connecting uv coordinates

    //unbind the VBO and VAO
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

    while (window.userRequestedExit() == false) {
        //render a frame
        glClearColor(0, 0, 0, 1);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        //bind the program
        glUseProgram(program.getProgram());
        
        //bind the VAO
        glBindVertexArray(vertexArrayObject);

        //draw the VAO
        glDrawArrays(GL_TRIANGLES, 0, 3);

        //unbind the VAO

        glBindVertexArray(0);

        //unbind the program
        glUseProgram(0);

        //swap the display buffers
        SDL_GL_SwapWindow(window.window);
    }

    //Close SDL
    SDL_Quit();
    IMG_Quit();
    return 0;
}
