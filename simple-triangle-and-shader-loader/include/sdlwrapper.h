#ifndef SDLWRAPPER_H
#define SDLWRAPPER_H

#include <SDL2/SDL.h>

class SDLWrapper
{
    private:
        SDL_Event event;
    public:
        SDL_GLContext glContext;
        SDL_Window *window;
        SDLWrapper(int winWidth, int winHeight);
        ~SDLWrapper();
        bool userRequestedQuit();
};

#endif
