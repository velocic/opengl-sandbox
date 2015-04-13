#include <GL/gl3w.h>
#include <SDL2/SDL.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/string_cast.hpp>
#include <vector>
#include <string>
#include <iostream>
#include <shader.h>
#include <programlinker.h>

void computePositionOffsets(float &xOffset, float &yOffset);

int main()
{
    //init
    SDL_Init(SDL_INIT_VIDEO | SDL_INIT_EVENTS);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);
    SDL_Window *window = SDL_CreateWindow(
        "Model-View-Projection Matrices",
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

    glm::mat4 projectionMatrix = glm::perspective(45.0f, 4.0f / 3.0f, 0.1f, 100.0f); //45 degree FoV, 4:3 aspect ratio, .1 "near clip", 100 "far clip"
    glm::mat4 viewMatrix = glm::lookAt(
        glm::vec3(4, 3, 3), //Camera is at (4, 3, 3) in world space
        glm::vec3(0, 0, 0), //looking at the origin (of world space)
        glm::vec3(0, 1, 0)  //Head is up (looking "down" towards the origin?)
    );
    glm::mat4 modelMatrix = glm::translate(glm::mat4(), glm::vec3()); //modelMatrix is set to the identity matrix
    
    //compose the matrices together
    glm::mat4 modelViewProjection = projectionMatrix * viewMatrix * modelMatrix; //the multiplication needs to be in this order

    std::cout <<"Contents of the MVP matrix: " << glm::to_string(modelViewProjection) << std::endl;

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

    GLuint mvpUniformLocation = program.getUniformLocation("modelViewProjectionMatrix");
    glUniformMatrix4fv(mvpUniformLocation, 1, GL_FALSE, &modelViewProjection[0][0]);

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
