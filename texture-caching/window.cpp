#include <window.h>

Window::Window(std::string title, int width, int height)
{
    window = SDL_CreateWindow(
        title.c_str(),
        SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED,
        width,
        height,
        SDL_WINDOW_OPENGL
    );

    glContext = SDL_GL_CreateContext(window);
}

Window::~Window()
{
    SDL_GL_DeleteContext(glContext);
    SDL_DestroyWindow(window);
}

bool Window::userRequestedExit()
{
    bool quit = false;

    while (SDL_PollEvent(&event)) {
        if (event.type == SDL_QUIT || event.key.keysym.sym == SDLK_ESCAPE) {
            quit = true;
        }
    }

    return quit;
}
