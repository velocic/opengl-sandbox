#include <shaderloader.h>

ShaderLoader::~ShaderLoader()
{
    if (shader != 0) {
        glDeleteShader(shader);
    }

    if (shaderProgram != 0) {
        glDetachShader(shaderProgram, shader);
    }
}

void ShaderLoader::importShaderSourceFromFile(std::string &shaderSource, const std::string &sourceFilePath)
{
    shaderSource = "";
    std::ifstream inFile(sourceFilePath);
    auto end = std::istreambuf_iterator<char>();
    for (auto iterator = std::istreambuf_iterator<char>(inFile); iterator != end; ++iterator) {
        shaderSource += (*iterator);
    }
}


bool ShaderLoader::compileShader()
{
    //grab the shader source from text file
    importShaderSourceFromFile(shaderSource, sourceFilePath);

    //create a handle to a shader of the type requested
    shader = glCreateShader(shaderType);
    const GLchar *source = (const GLchar *)shaderSource.c_str();

    //push our text source to the GPU, then attempt to compile it
    glShaderSource(shader, 1, &source, 0);
    glCompileShader(shader);

    //retrieve the compile status of the shader from the GPU
    GLint compiledProperly = 0;
    glGetShaderiv(shader, GL_COMPILE_STATUS, &compiledProperly);
    if (compiledProperly == GL_FALSE)
    {
        logShaderCompilationError(shader);
        glDeleteShader(shader);
        return false;
    }

    // //create the shader program
    // shaderProgram = glCreateProgram();
    //
    // //attach the shader object to the program
    // glAttachShader(shaderProgram, shader);
    
    return true;
}

void ShaderLoader::logShaderCompilationError(const GLuint &shader)
{
    std::cout << "Printing compilation error for " << sourceFilePath << "..." << std::endl;
    //retrieve shader's info log
    GLint maxLength = 0;
    glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &maxLength);
    std::vector<GLchar> infoLog(maxLength);
    glGetShaderInfoLog(shader, maxLength, &maxLength, &infoLog[0]);

    //print the log
    for (char c : infoLog) {
        std::cout << c;
    }
    std::cout << std::endl;
}
