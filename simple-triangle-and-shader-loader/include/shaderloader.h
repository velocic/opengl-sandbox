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
        GLenum shaderType;
        void importShaderSourceFromFile(std::string &shaderSource, const std::string &sourceFilePath);
    public:
        ShaderLoader(GLenum shaderType, std::string sourceFilePath) :
            shaderType(shaderType),
            sourceFilePath(sourceFilePath) {};
        ~ShaderLoader();
        bool compileShader();
        void debug();
};

#endif
