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
    
    Shader vertex(GL_VERTEX_SHADER, "shaders/vertex.glsl");
    Shader fragment(GL_FRAGMENT_SHADER, "shaders/fragment.glsl");
    //load shaders into vector
    std::vector<Shader> shaders = {vertex, fragment};
    //pass vector into programlinker
    ProgramLinker program(shaders);

    while(sdl.userRequestedQuit() == false)
    {
        //Do rendering here
    }


    SDL_Quit();
    return 0;
}
