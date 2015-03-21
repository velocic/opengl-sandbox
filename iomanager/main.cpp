#include <GL/glew.h>
#include <SDL2/SDL.h>
#include <shader.h>
#include <programlinker.h>
#include <window.h>
#include <iostream>
#include <vector>
#include <ioutils.h>
#include <sprite.h>
#include <gltexture.h>

int main()
{
    SDL_Init(SDL_INIT_VIDEO | SDL_INIT_EVENTS);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 1);

    //Open a window (and create a GL context)
    Window window("Shader loading!", 640, 480);
    //init glew
    GLenum initStatus = glewInit();
    if (initStatus != GLEW_OK) {
        std::cout << "glewInit() failed: " << glewGetErrorString(initStatus) << std::endl;
        return 1;
    }

    Sprite sprite;
    sprite.init(-1.0f, -1.0f, 2.0f, 2.0f);
    Shader frag(GL_FRAGMENT_SHADER, "shaders/colorshading.frag");
    Shader vert(GL_VERTEX_SHADER, "shaders/colorshading.vert");
    std::vector<Shader> shaders = {frag, vert};
    ProgramLinker colorProgram(shaders);
    colorProgram.link();
    colorProgram.addAttribute("vertexPosition");
    colorProgram.addAttribute("vertexColor");

    //lets load up a texture
    GLTexture playerTexture;
    playerTexture = IOUtils::loadPNG("textures/PNG/CharacterRight_Standing.png");

    GLuint timeLocation = 0;
    float time = 0;
    while (!window.userRequestedExit()) {
        time += .01;
        //set the base depth to 1.0
        glClearDepth(1.0);

        //clear the color and depth buffer
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        colorProgram.use();
        timeLocation = colorProgram.getUniformLocation("time");
        //send time to the timeLocation uniform var in the fragment shader
        glUniform1f(timeLocation, time);
        sprite.draw();
        colorProgram.unuse();

        //Show the rendered screen
        SDL_GL_SwapWindow(window.window);
    }

    SDL_Quit();
    return 0;
}
