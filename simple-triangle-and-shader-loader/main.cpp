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

//mine
#include <sdlwrapper.h>
#include <shaderloader.h>

void importShaders();
void defineTriangle();
void bufferTriangle();
void renderTriangle();

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
    
    ShaderLoader vertex(GL_VERTEX_SHADER, "shaders/vertex.glsl");
    ShaderLoader fragment(GL_FRAGMENT_SHADER, "shaders/fragment.glsl");
    // ShaderLoader vertex(GL_VERTEX_SHADER, "blah.txt");
    vertex.compileShader();
    fragment.compileShader();

    while(sdl.userRequestedQuit() == false)
    {
        //Do rendering here
    }


    SDL_Quit();
    return 0;
}
