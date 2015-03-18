#include <GL/glew.h>
#include <SDL2/SDL.h>
#include <shader.h>
#include <programlinker.h>
#include <window.h>
#include <iostream>
#include <vector>
#include <sprite.h>

int main()
{
    SDL_Init(SDL_INIT_VIDEO | SDL_INIT_EVENTS);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);

    //Open a window (and create a GL context)
    Window window("Learning about vertex buffering!", 640, 480);
    //init glew
    GLenum initStatus = glewInit();
    if (initStatus != GLEW_OK) {
        std::cout << "glewInit() failed: " << glewGetErrorString(initStatus) << std::endl;
    }

    Sprite sprite;
    sprite.init(-1.0f, -1.0f, 1.0f, 1.0f);

    //need placeholder shaders to get anything to draw
    Shader fragment(GL_FRAGMENT_SHADER, "shaders/fragment.glsl");
    Shader vertex(GL_VERTEX_SHADER, "shaders/vertex.glsl");
    std::vector<Shader> shaders = {fragment, vertex};
    ProgramLinker program(shaders);
    program.link();

    while (!window.userRequestedExit()) {
        //do stuff
        //set the base depth to 1.0
        glClearColor(0, 0, 0, 1);
        glClearDepth(1.0);

        //clear the color and depth buffer
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        glUseProgram(program.getProgram());

        sprite.draw();

        glUseProgram(0);

        SDL_GL_SwapWindow(window.window);
    }

    SDL_Quit();
    return 0;
}
