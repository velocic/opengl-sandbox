#ifndef WINDOW_H
#define WINDOW_H

#include <SDL2/SDL.h>
#include <GL/gl3w.h>
#include <string>

class Window
{
    private:
        SDL_Event event;
        SDL_GLContext glContext;
    public:
        SDL_Window *window;
        Window(std::string title, int width, int height);
        ~Window();
        bool userRequestedExit();
};

#endif
