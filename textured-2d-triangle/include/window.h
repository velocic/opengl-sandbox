#ifndef WINDOW_H
#define WINDOW_H

#include <SDL2/SDL.h>
#include <GL/glew.h>

class Window
{
    private:
        SDL_Event event;
        SDL_GLContext glContext;
    public:
        SDL_Window *window;
        Window(int width, int height);
        ~Window();
        bool userRequestedExit();
};

#endif
