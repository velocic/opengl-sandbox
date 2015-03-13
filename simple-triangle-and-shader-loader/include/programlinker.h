#ifndef PROGRAMLINKER_H
#define PROGRAMLINKER_H

#include <GL/glew.h>
#include <iostream>
#include <shader.h>
#include <vector>

class ProgramLinker
{
    private:
        std::vector<Shader> shaders;
        GLuint program = 0;
        void compileAndAttachShaders(std::vector<Shader> &shaders, const GLuint &program);
        void detachAndUnloadShaders(std::vector<Shader> &shaders, const GLuint &program);
        void logLinkError(const GLuint &program);
    public:
        ProgramLinker(std::vector<Shader> shaders) : shaders(shaders) {};
        ~ProgramLinker();
        GLuint getProgram();
        bool link();
        void unload();
};

#endif
