#ifndef SHADERLOADER_H
#define SHADERLOADER_H

#include <GL/glew.h>
#include <string>
#include <vector>
#include <fstream>
#include <iostream>

class ShaderLoader
{
    private:
        std::string sourceFilePath;
        std::string shaderSource;
        GLuint shaderProgram = 0;
        GLenum shaderType;
        GLuint shader = 0;
        void importShaderSourceFromFile(std::string &shaderSource, const std::string &sourceFilePath);
        void logShaderCompilationError(const GLuint &shader);
    public:
        ShaderLoader(GLenum shaderType, std::string sourceFilePath) :
            shaderType(shaderType),
            sourceFilePath(sourceFilePath) {};
        ~ShaderLoader();
        bool compileShader();
};

#endif
