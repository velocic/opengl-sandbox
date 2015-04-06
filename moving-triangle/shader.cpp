#include <shader.h>

Shader::~Shader()
{
    unload();
}

void Shader::importSourceFromFile(std::string &shaderSource, const std::string &sourceFilePath)
{
    shaderSource = "";
    std::ifstream inFile(sourceFilePath);
    if (inFile.fail()) {
        std::cout << "Failed to open " << sourceFilePath << "." << std::endl;
        //TODO: throw an exception here, or something
    }
    inFile.seekg(0, std::ios::end);
    shaderSource.reserve(inFile.tellg());
    inFile.seekg(0, std::ios::beg);
    shaderSource.assign(
        (std::istreambuf_iterator<char>(inFile)),
        std::istreambuf_iterator<char>()
    );
}

void Shader::logCompilationError(const GLuint &shader)
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

void Shader::attachToProgram(GLuint program)
{
    if (program == 0) {
        std::cout << "Tried to attach shader to null program. Aborting." << std::endl;
        return;
    } else if (shader == 0) {
        std::cout << "Tried to attach null shader to program. Aborting." << std::endl;
        return;
    }
    glAttachShader(program, shader);
}

bool Shader::compile()
{
    //if we've already created a shader, unload it before we recompile
    unload();

    //grab the shader source from text file
    importSourceFromFile(shaderSource, sourceFilePath);

    //create a handle to a shader of the type requested
    //TODO: check shader != 0. if it is, we failed to create a shader object
    shader = glCreateShader(shaderType);
    const GLchar *source = (const GLchar *)shaderSource.c_str();

    //push our text source to the GPU, then attempt to compile it
    glShaderSource(shader, 1, &source, 0);
    glCompileShader(shader);

    //retrieve the compile status of the shader from the GPU
    GLint compiledProperly = 0;
    glGetShaderiv(shader, GL_COMPILE_STATUS, &compiledProperly);
    if (compiledProperly == GL_FALSE) {
        logCompilationError(shader);
        unload();
        return false;
    }

    return true;
}

void Shader::detachFromProgram(GLuint program)
{
    if (program == 0) {
        std::cout << "Tried to detach shader from null program. Aborting." << std::endl;
        return;
    } else if (shader == 0) {
        std::cout << "Tried to detach null shader from program. Aborting." << std::endl;
        return;
    }
    glDetachShader(program, shader);
}

void Shader::unload()
{
    if (shader != 0) {
        glDeleteShader(shader);
    }

    shader = 0;
}
