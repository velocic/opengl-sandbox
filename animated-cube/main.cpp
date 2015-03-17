#include <GL/glew.h>
#include <glm/glm.hpp>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <shader.h>
#include <programlinker.h>
#include <window.h>
#include <vector>

int main()
{
    //Start SDL
    SDL_Init(SDL_INIT_VIDEO | SDL_INIT_EVENTS);
    IMG_Init(IMG_INIT_PNG);
    //request a core OpenGL profile
    SDL_GL_SetAttribute( SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE );
    SDL_GL_SetAttribute( SDL_GL_CONTEXT_MAJOR_VERSION, 3);
    SDL_GL_SetAttribute( SDL_GL_CONTEXT_MINOR_VERSION, 3);

    //create the window, create an opengl context
    Window window("Animated Box! Early Access Edition", 640, 480);
    //start OpenGL
    glewExperimental = GL_TRUE;
    GLenum error = glewInit();
    if (error != GLEW_OK) {
        std::cout << glewGetErrorString(error) << std::endl;
        return 1;
    }

    while (!window.userRequestedExit())
    {
        //do stuff
    }

    SDL_Quit();
    IMG_Quit();
    return 0;
}
