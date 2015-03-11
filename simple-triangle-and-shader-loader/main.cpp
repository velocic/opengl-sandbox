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
    //os x compatibility :(
    glewExperimental = GL_TRUE;
    //Init SDL & OpenGL
    SDL_Init(SDL_INIT_VIDEO);
    SDL_GL_SetAttribute( SDL_GL_CONTEXT_MAJOR_VERSION, 3 );
    SDL_GL_SetAttribute( SDL_GL_CONTEXT_MINOR_VERSION, 3 );
    SDL_GL_SetAttribute( SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE );
    GLenum error = glewInit();
    std::cout << error << std::endl;
    if (error != GLEW_OK)
        return 1;
    //end initialization
    
    SDLWrapper sdl(640, 480);

    while(sdl.userRequestedQuit() == false)
    {
        glClearColor(0,1,1,1);
        glClear(GL_COLOR_BUFFER_BIT);
        SDL_GL_SwapWindow(sdl.window);
    }

    ShaderLoader loader(GL_VERTEX_SHADER, "blah.txt");
    loader.debug();

    SDL_Quit();
    return 0;
}
