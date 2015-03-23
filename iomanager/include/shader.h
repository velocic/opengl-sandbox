#ifndef SHADER_H
#define SHADER_H

#include <GL/gl3w.h>
#include <string>
#include <vector>
#include <fstream>
#include <iostream>

class Shader
{
    private:
        std::string sourceFilePath;
        std::string shaderSource;
        GLenum shaderType;
        GLuint shader = 0;
        void importSourceFromFile(std::string &shaderSource, const std::string &sourceFilePath);
        void logCompilationError(const GLuint &shader);
    public:
        Shader(GLenum shaderType, std::string sourceFilePath) :
            shaderType(shaderType),
            sourceFilePath(sourceFilePath) {};
        ~Shader();
        bool compile();
        GLuint getOGLHandle();
        void unload();
};

#endif
