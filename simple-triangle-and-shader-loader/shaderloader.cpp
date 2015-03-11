#include <shaderloader.h>

void ShaderLoader::importShaderSourceFromFile(std::string &shaderSource, const std::string &sourceFilePath)
{
    shaderSource = "";
    std::ifstream inFile(sourceFilePath);
    auto end = std::istreambuf_iterator<char>();
    for (auto iterator = std::istreambuf_iterator<char>(inFile); iterator != end; ++iterator) {
        shaderSource += (*iterator);
    }
}

ShaderLoader::~ShaderLoader()
{
}

bool ShaderLoader::compileShader()
{
    // GLuint shader = glCreateShader(shaderType);
    // const GLchar *source = (const GLchar *)shaderSource.c_str();
    //
    // glShaderSource(shader, 1, &source, 0);
    // glCompileShader(shader);
    //
    // GLint compiledProperly = 0;
    // glGetShaderiv(shader, GL_COMPILE_STATUS, &compiledProperly);
    //
    // if (compiledProperly == GL_FALSE)
    // {
    //     //retrieve shader's info log
    //     GLint maxLength = 0;
    //     glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &maxLength);
    //     std::vector<GLchar> infoLog(maxLength);
    //     glGetShaderInfoLog(shader, maxLength, &maxLength, &infoLog[0]);
    //
    //     //throw away the shader
    //     glDeleteShader(shader);
    //
    //     // //print the log
    //     // for (char c : infoLog) {
    //     //     std::cout << c;
    //     // }
    //     // std::cout << std::endl;
    //
    //     return false;
    // }
    
    return true;
}

void ShaderLoader::debug()
{
    importShaderSourceFromFile(shaderSource, sourceFilePath);
    std::cout << shaderSource << std::endl;
    // compileShader();
}
