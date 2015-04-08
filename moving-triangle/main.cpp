#include <GL/gl3w.h>
#include <SDL2/SDL.h>
#include <vector>
#include <string>
#include <iostream>
#include <shader.h>
#include <programlinker.h>
#include <cmath>

void computePositionOffsets(float &xOffset, float &yOffset);

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
    GLuint vbo = 0;
    GLuint vao = 0;
    float vertexPositions[] = {
        0.3f, 0.3f, 0.0f, 1.0f,
        0.3f, -0.3f, 0.0f, 1.0f,
        -0.3f, -0.3f, 0.0f, 1.0f
    };


    //load shaders, create program
    Shader vert(GL_VERTEX_SHADER, "shaders/shader.vert");
    Shader frag(GL_FRAGMENT_SHADER, "shaders/shader.frag");
    std::vector<Shader> shaders = {
        vert,
        frag
    };
    ProgramLinker program(shaders);
    program.link();
    program.use();
    
    //Load vertex data into a buffer pointed to by vbo
    glGenBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertexPositions), vertexPositions, GL_STATIC_DRAW);

    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 0, 0);

    //get the index for our "offset" uniform variable in the vertex shader
    GLint loopDurationIndex = program.getUniformLocation("loopDuration");
    GLint timeIndex = program.getUniformLocation("time");
    glUniform1f(loopDurationIndex, 5.0f);

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
        // computePositionOffsets(xOffset, yOffset);
        //handle drawing
        glClearColor(0.0f, 0.0f, 1.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        // glUniform2f(offsetIndex, xOffset, yOffset);
        glUniform1f(timeIndex, SDL_GetTicks() / 1000.0f);
        glDrawArrays(GL_TRIANGLES, 0, 3);
        SDL_GL_SwapWindow(window);
    }


    //clean up
    program.unuse();
    glDisableVertexAttribArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    SDL_GL_DeleteContext(glContext);
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}

void computePositionOffsets(float &xOffset, float &yOffset)
{
    float loopDuration = 5.0f;
    float scale = 3.14159f * 2.0f / loopDuration;

    float elapsedTime = SDL_GetTicks() / 1000.0f;

    float currTimeThroughLoop = fmodf(elapsedTime, loopDuration);

    xOffset = cosf(currTimeThroughLoop * scale) * 0.5f;
    yOffset = sinf(currTimeThroughLoop * scale) * 0.5f;
}
