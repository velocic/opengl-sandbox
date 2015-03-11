#include <sdlwrapper.h>

SDLWrapper::SDLWrapper(int winWidth, int winHeight)
{
    window = SDL_CreateWindow(
        "OpenGL with SDL2",
        SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED,
        winWidth,
        winHeight,
        SDL_WINDOW_OPENGL
    );
    glContext = SDL_GL_CreateContext(window);
}

SDLWrapper::~SDLWrapper()
{
    SDL_GL_DeleteContext(glContext);
    SDL_DestroyWindow(window);
}

bool SDLWrapper::userRequestedQuit()
{
    bool userRequestedQuit = false;
    while (SDL_PollEvent(&event)) {
        if (event.type == SDL_QUIT) {
            userRequestedQuit = true;
        }
    }

    return userRequestedQuit;
}
