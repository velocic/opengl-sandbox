/*
 * Steps:
 * import + compile shaders
 * define + render triangle
 * set VBO + VAO with triangle data
 */

//third party
#include <SDL2/SDL.h>
#include <GL/glew.h>
#include <SDL2/SDL_opengl.h>
#include <glm/glm.hpp>

//standard c++
#include <iostream>
#include <string>
#include <vector>

//mine
#include <sdlwrapper.h>
#include <shader.h>
#include <programlinker.h>

GLuint gVAO;
GLuint gVBO;

int main()
{
    //Init SDL & OpenGL
    SDL_Init(SDL_INIT_VIDEO);
    SDL_GL_SetAttribute( SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE );
    SDL_GL_SetAttribute( SDL_GL_CONTEXT_MAJOR_VERSION, 3);
    SDL_GL_SetAttribute( SDL_GL_CONTEXT_MINOR_VERSION, 3);
    SDLWrapper sdl(640, 480);

    glewExperimental = GL_TRUE;
    GLenum error = glewInit();
    if (error != GLEW_OK) {
        std::cout << glewGetErrorString(error) << std::endl;
        return 1;
    }
    //end initialization
    
    Shader vertex(GL_VERTEX_SHADER, "shaders/vertex.glsl");
    Shader fragment(GL_FRAGMENT_SHADER, "shaders/fragment.glsl");
    //load shaders into vector
    std::vector<Shader> shaders = {vertex, fragment};
    //pass vector into programlinker
    ProgramLinker program(shaders);
    program.link();

    //create and bind a vertex array object
    glGenVertexArrays(1, &gVAO);
    glBindVertexArray(gVAO);

    //create and bind a vertex buffer object
    glGenBuffers(1, &gVBO);
    glBindBuffer(GL_ARRAY_BUFFER, gVBO);

    //upload triangle  vertices to the VBO
    GLfloat vertexData[] = {
        //x,y,z
        0.0f, 0.8f, 0.0f,
        -0.8f, -0.8f, 0.0f,
        0.8f, -0.8f, 0.0f
    };
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertexData), vertexData, GL_STATIC_DRAW);
    GLint attrib = glGetAttribLocation(program.getProgram(), "vert");
    glEnableVertexAttribArray(attrib);

    glVertexAttribPointer(attrib, 3, GL_FLOAT, GL_FALSE, 0, NULL);

    //unbind the VBO and VAO
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

    while(sdl.userRequestedQuit() == false)
    {
        //render a frame
        glClearColor(0, 0, 0, 1);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        //bind the program
        glUseProgram(program.getProgram());
        
        //bind the VAO
        glBindVertexArray(gVAO);

        //draw the VAO
        glDrawArrays(GL_TRIANGLES, 0, 3);

        //unbind the VAO

        glBindVertexArray(0);

        //unbind the program
        glUseProgram(0);

        //swap the display buffers
        SDL_GL_SwapWindow(sdl.window);
    }


    SDL_Quit();
    return 0;
}
