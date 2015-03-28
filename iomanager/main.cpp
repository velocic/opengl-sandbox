#include <GL/gl3w.h>
#include <SDL2/SDL.h>
#include <iostream>
#include <shader.h>
#include <programlinker.h>
#include <window.h>
#include <ioutils.h>
#include <sprite.h>
#include <vector>
#include <gltexture.h>

int main()
{
    SDL_Init(SDL_INIT_VIDEO | SDL_INIT_EVENTS);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);

    //Open a window (and create a GL context)
    Window window("Shader loading!", 640, 480);
    //init gl3w
    if (gl3wInit() < 0) {
        std::cout << "gl3w failed to initialize OpenGL" << std::endl;
        return -1;
    }

    Sprite sprite;
    sprite.init(-1.0f, -1.0f, 2.0f, 2.0f);
    Shader frag(GL_FRAGMENT_SHADER, "shaders/colorshading.frag");
    Shader vert(GL_VERTEX_SHADER, "shaders/colorshading.vert");
    std::vector<Shader> shaders = {frag, vert};
    ProgramLinker colorProgram(shaders);

    if (!colorProgram.link()) {
        std::cout << "program failed to link! aborting." << std::endl;
        return -1;
    }
    colorProgram.addAttribute("vertexPosition");
    colorProgram.addAttribute("vertexColor");
    colorProgram.addAttribute("vertexUV");

    //lets load up a texture
    GLTexture playerTexture;
    playerTexture = IOUtils::loadPNG("textures/PNG/CharacterRight_Standing.png");

    GLuint timeLocation = 0;
    GLint textureLocation = 0;
    float time = 0;
    while (!window.userRequestedExit()) {
        time += .01;
        //set the base depth to 1.0
        glClearDepth(1.0);

        //clear the color and depth buffer
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        colorProgram.use();
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, playerTexture.id);
        textureLocation = colorProgram.getUniformLocation("playerTexture");
        glUniform1i(textureLocation, 0);
        timeLocation = colorProgram.getUniformLocation("time");
        // send time to the timeLocation uniform var in the fragment shader
        glUniform1f(timeLocation, time);
        sprite.draw();
        colorProgram.unuse();

        glBindTexture(GL_TEXTURE_2D, 0);
        //Show the rendered screen
        SDL_GL_SwapWindow(window.window);
    }

    SDL_Quit();
    return 0;
}
