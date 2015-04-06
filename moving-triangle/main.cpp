#include <GL/gl3w.h>
#include <SDL2/SDL.h>
#include <vector>
#include <string>
#include <iostream>

int main()
{
    //init
    SDL_Init(SDL_INIT_VIDEO | SDL_INIT_EVENTS);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);
    SDL_Window *window = SDL_CreateWindow(
        "Moving triangle!",
        SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED,
        640,
        480,
        SDL_WINDOW_OPENGL
    );
    SDL_GLContext glContext = SDL_GL_CreateContext(window);

    if (gl3wInit() < 0) {
        std::cout << "gl3w failed to initialize OpenGL" << std::endl;
        return -1;
    }


    //Buffer Vertices (VBO, VAO)
    
    //"game" loop
    SDL_Event e;
    bool userRequestedQuit = false;
    while (userRequestedQuit == false) {
        //handle events
        while (SDL_PollEvent(&e)) {
            if (e.key.keysym.sym == SDLK_ESCAPE) {
                userRequestedQuit = true;
            }
        }
        //handle drawing
        
        glClearColor(0.0f, 0.0f, 1.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        SDL_GL_SwapWindow(window);
    }


    //clean up
    SDL_GL_DeleteContext(glContext);
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}
