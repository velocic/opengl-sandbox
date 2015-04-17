#include <GL/gl3w.h>
#include <SDL2/SDL.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <shader.h>
#include <programlinker.h>
#include <string>
#include <vector>
#include <iostream>
#include <controls.h>
#include <bmploader.h>

int main()
{
    //initialize sdl + ogl
    SDL_Init(SDL_INIT_VIDEO | SDL_INIT_EVENTS);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);

    SDL_Window *window = SDL_CreateWindow(
        "3D Cube!",
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

    Shader vert(GL_VERTEX_SHADER, "shaders/basicshader.vert");
    Shader frag(GL_FRAGMENT_SHADER, "shaders/basicshader.frag");
    std::vector<Shader> shaders = {vert, frag};
    ProgramLinker program(shaders);
    program.link();
    program.use();

    //sample vertices for a 3d cube
    GLfloat cubeVertices[] = {
        -1.0f,-1.0f,-1.0f, // triangle 1 : begin
        -1.0f,-1.0f, 1.0f,
        -1.0f, 1.0f, 1.0f, // triangle 1 : end
        1.0f, 1.0f,-1.0f, // triangle 2 : begin
        -1.0f,-1.0f,-1.0f,
        -1.0f, 1.0f,-1.0f, // triangle 2 : end
        1.0f,-1.0f, 1.0f,
        -1.0f,-1.0f,-1.0f,
        1.0f,-1.0f,-1.0f,
        1.0f, 1.0f,-1.0f,
        1.0f,-1.0f,-1.0f,
        -1.0f,-1.0f,-1.0f,
        -1.0f,-1.0f,-1.0f,
        -1.0f, 1.0f, 1.0f,
        -1.0f, 1.0f,-1.0f,
        1.0f,-1.0f, 1.0f,
        -1.0f,-1.0f, 1.0f,
        -1.0f,-1.0f,-1.0f,
        -1.0f, 1.0f, 1.0f,
        -1.0f,-1.0f, 1.0f,
        1.0f,-1.0f, 1.0f,
        1.0f, 1.0f, 1.0f,
        1.0f,-1.0f,-1.0f,
        1.0f, 1.0f,-1.0f,
        1.0f,-1.0f,-1.0f,
        1.0f, 1.0f, 1.0f,
        1.0f,-1.0f, 1.0f,
        1.0f, 1.0f, 1.0f,
        1.0f, 1.0f,-1.0f,
        -1.0f, 1.0f,-1.0f,
        1.0f, 1.0f, 1.0f,
        -1.0f, 1.0f,-1.0f,
        -1.0f, 1.0f, 1.0f,
        1.0f, 1.0f, 1.0f,
        -1.0f, 1.0f, 1.0f,
        1.0f,-1.0f, 1.0f
    }; 

    // Two UV coordinatesfor each vertex. They were created with Blender. You'll learn shortly how to do this yourself.
    GLfloat UVData[] = {
        0.000059f, 1.0f-0.000004f,
        0.000103f, 1.0f-0.336048f,
        0.335973f, 1.0f-0.335903f,
        1.000023f, 1.0f-0.000013f,
        0.667979f, 1.0f-0.335851f,
        0.999958f, 1.0f-0.336064f,
        0.667979f, 1.0f-0.335851f,
        0.336024f, 1.0f-0.671877f,
        0.667969f, 1.0f-0.671889f,
        1.000023f, 1.0f-0.000013f,
        0.668104f, 1.0f-0.000013f,
        0.667979f, 1.0f-0.335851f,
        0.000059f, 1.0f-0.000004f,
        0.335973f, 1.0f-0.335903f,
        0.336098f, 1.0f-0.000071f,
        0.667979f, 1.0f-0.335851f,
        0.335973f, 1.0f-0.335903f,
        0.336024f, 1.0f-0.671877f,
        1.000004f, 1.0f-0.671847f,
        0.999958f, 1.0f-0.336064f,
        0.667979f, 1.0f-0.335851f,
        0.668104f, 1.0f-0.000013f,
        0.335973f, 1.0f-0.335903f,
        0.667979f, 1.0f-0.335851f,
        0.335973f, 1.0f-0.335903f,
        0.668104f, 1.0f-0.000013f,
        0.336098f, 1.0f-0.000071f,
        0.000103f, 1.0f-0.336048f,
        0.000004f, 1.0f-0.671870f,
        0.336024f, 1.0f-0.671877f,
        0.000103f, 1.0f-0.336048f,
        0.336024f, 1.0f-0.671877f,
        0.335973f, 1.0f-0.335903f,
        0.667969f, 1.0f-0.671889f,
        1.000004f, 1.0f-0.671847f,
        0.667979f, 1.0f-0.335851f
    };

    GLuint textureID = BMPLoader::loadBMP_custom("uvtemplate.bmp");
    glBindTexture(GL_TEXTURE_2D, textureID);

    // GLfloat cubeVertexColors[] = {
    //     0.583f,  0.771f,  0.014f,
    //     0.609f,  0.115f,  0.436f,
    //     0.327f,  0.483f,  0.844f,
    //     0.822f,  0.569f,  0.201f,
    //     0.435f,  0.602f,  0.223f,
    //     0.310f,  0.747f,  0.185f,
    //     0.597f,  0.770f,  0.761f,
    //     0.559f,  0.436f,  0.730f,
    //     0.359f,  0.583f,  0.152f,
    //     0.483f,  0.596f,  0.789f,
    //     0.559f,  0.861f,  0.639f,
    //     0.195f,  0.548f,  0.859f,
    //     0.014f,  0.184f,  0.576f,
    //     0.771f,  0.328f,  0.970f,
    //     0.406f,  0.615f,  0.116f,
    //     0.676f,  0.977f,  0.133f,
    //     0.971f,  0.572f,  0.833f,
    //     0.140f,  0.616f,  0.489f,
    //     0.997f,  0.513f,  0.064f,
    //     0.945f,  0.719f,  0.592f,
    //     0.543f,  0.021f,  0.978f,
    //     0.279f,  0.317f,  0.505f,
    //     0.167f,  0.620f,  0.077f,
    //     0.347f,  0.857f,  0.137f,
    //     0.055f,  0.953f,  0.042f,
    //     0.714f,  0.505f,  0.345f,
    //     0.783f,  0.290f,  0.734f,
    //     0.722f,  0.645f,  0.174f,
    //     0.302f,  0.455f,  0.848f,
    //     0.225f,  0.587f,  0.040f,
    //     0.517f,  0.713f,  0.338f,
    //     0.053f,  0.959f,  0.120f,
    //     0.393f,  0.621f,  0.362f,
    //     0.673f,  0.211f,  0.457f,
    //     0.820f,  0.883f,  0.371f,
    //     0.982f,  0.099f,  0.879f
    // };

    //Buffer the vertices for the cube
    GLuint cubeVBO;
    glGenBuffers(1, &cubeVBO);
    glBindBuffer(GL_ARRAY_BUFFER, cubeVBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(cubeVertices), cubeVertices, GL_STATIC_DRAW);
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    //Buffer the colors for the cube's vertices
    // GLuint cubeColorVBO;
    // glGenBuffers(1, &cubeColorVBO);
    // glBindBuffer(GL_ARRAY_BUFFER, cubeColorVBO);
    // glBufferData(GL_ARRAY_BUFFER, sizeof(cubeVertexColors), cubeVertexColors, GL_STATIC_DRAW);
    // glBindBuffer(GL_ARRAY_BUFFER, 0);

    //Buffer the UV data
    GLuint uvVBO;
    glGenBuffers(1, &uvVBO);
    glBindBuffer(GL_ARRAY_BUFFER, uvVBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(UVData), UVData, GL_STATIC_DRAW); 
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    //Associate buffered data with the position & color vec4 variables in the shader program
    GLuint cubeVAO;
    glGenVertexArrays(1, &cubeVAO);
    glBindVertexArray(cubeVAO);
    glEnableVertexAttribArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, cubeVBO);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    // glEnableVertexAttribArray(1);
    // glBindBuffer(GL_ARRAY_BUFFER, cubeColorVBO);
    // glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, 0);
    glEnableVertexAttribArray(1);
    glBindBuffer(GL_ARRAY_BUFFER, uvVBO);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, 0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);



    //event + draw loop
    Controls controls;
    SDL_Event e;
    bool userRequestedQuit = false;
    //set up mvp matrix variables
    glm::mat4 projection;
    glm::mat4 view;
    glm::mat4 model;
    glm::mat4 mvpMatrix;
    GLuint mvpUniform = program.getUniformLocation("modelViewProjection");
    //quick and hacky movement offsets
    float xOffset = 0;
    float zOffset = 0;
    float yOffset = 0;
    float pan = 0;
    float tilt = 0;
    float previousMouseX = 0;
    float previousMouseY = 0;

    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);

    while (!userRequestedQuit) {
        //handle events
        while (SDL_PollEvent(&e)) {
            if (e.key.keysym.sym == SDLK_ESCAPE || e.type == SDL_QUIT) {
                userRequestedQuit = true;
            }
        }

        //quick and hacky calculation of move offsets
        if (controls.getKeyStatus(Keys::Forward)) {
            zOffset -= 0.1f;
        }

        if (controls.getKeyStatus(Keys::Back)) {
            zOffset += 0.1f;
        }

        if (controls.getKeyStatus(Keys::Right)) {
            xOffset += 0.1f;
        }

        if (controls.getKeyStatus(Keys::Left)) {
            xOffset -= 0.1f;
        }

        if (controls.getKeyStatus(Keys::Ascend)) {
            yOffset += 0.1f;
        }

        if (controls.getKeyStatus(Keys::Descend)) {
            yOffset -= 0.1f;
        }

        if (e.motion.x > previousMouseX) {
            pan += 0.1f;
        }

        if (e.motion.x < previousMouseX) {
            pan -= 0.1f;
        }

        if (e.motion.y > previousMouseY) {
            tilt += 0.1f;
        }

        if (e.motion.y < previousMouseY) {
            tilt -= 0.1f;
        }
        previousMouseX = e.motion.x;
        previousMouseY = e.motion.y;


        //end calculating move offsets

        //Build the model-view-projection matrix for this cube
        projection = glm::perspective(45.0f, 4.0f / 3.0f, 0.1f, 100.0f);
        view = glm::lookAt(
            // hard-coded debug projection-space
            glm::vec3(xOffset,yOffset,zOffset+5), //camera location
            // glm::vec3(0,0,0), //looking at the origin
            // glm::vec3(0,1,0)  //looking upright
            // glm::vec3(xOffset, 0, zOffset), //camera location
            glm::vec3(xOffset + pan, yOffset + tilt, zOffset), //looking at this point
            glm::vec3(0, 1, 0) //looking upright
        );
        model = glm::translate(glm::mat4(), glm::vec3()); //identity matrix. cube should center at (0,0,0) for now
        
        mvpMatrix = projection * view * model;

        //send mvpMatrix into the modelViewProjection uniform of the shader program once per screen re-draw
        glUniformMatrix4fv(mvpUniform, 1, GL_FALSE, &mvpMatrix[0][0]);
        //End MVP matrix building

        //draw screen
        glClearColor(0.0f, 0.0f, 1.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glDrawArrays(GL_TRIANGLES, 0, 6*6);
        SDL_GL_SwapWindow(window);
    }
    
    program.unuse();
    glDisableVertexAttribArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    SDL_GL_DeleteContext(glContext);
    SDL_DestroyWindow(window);
    return 0;
}
