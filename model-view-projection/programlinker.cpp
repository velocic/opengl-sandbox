#include <programlinker.h>

ProgramLinker::~ProgramLinker()
{
    unload();
}

void ProgramLinker::addAttribute(const std::string &attributeName)
{
    glBindAttribLocation(program, numAttributes++, attributeName.c_str());
}

GLuint ProgramLinker::getUniformLocation(const std::string &uniformName)
{
    GLuint location = glGetUniformLocation(program, uniformName.c_str());
    if (location == GL_INVALID_INDEX) {
        std::cout << "error: " << uniformName << " not found in shader." << std::endl;
        return 0;
    }

    return location;
}

void ProgramLinker::compileAndAttachShaders(std::vector<Shader> &shaders, const GLuint &program)
{
    //TODO: we should abort if any shader fails to compile
    for (Shader &shader : shaders) {
        shader.compile();
        shader.attachToProgram(program);
    }
}

void ProgramLinker::detachAndUnloadShaders(std::vector<Shader> &shaders, const GLuint &program)
{
    for (Shader &shader : shaders) {
        shader.detachFromProgram(program);
        shader.unload();
    }

    //There is an error here where we call detach shader with a shader id of 0. this is because we call unload
    //at the beginning of link. need to fix
}

void ProgramLinker::logLinkError(const GLuint &program)
{
    //retrieve the program's info log
    GLint maxLength = 0;
    glGetProgramiv(program, GL_INFO_LOG_LENGTH, &maxLength);
    std::vector<GLchar> infoLog(maxLength);
    glGetProgramInfoLog(program, maxLength, &maxLength, &infoLog[0]);

    //print the log
    std::cout << "Failed to link program..." << std::endl;
    for (char c : infoLog) {
        std::cout << c;
    }
    std::cout << std::endl;
}

bool ProgramLinker::link()
{
    //if the program has previously been loaded, unload it
    unload();

    //initialize a program object
    program = glCreateProgram();

    //attach the shaders to the program
    compileAndAttachShaders(shaders, program);

    //link the program
    glLinkProgram(program);
    GLint isLinked = 0;
    glGetProgramiv(program, GL_LINK_STATUS, (int *)&isLinked);

    if (isLinked == GL_FALSE)
    {
        logLinkError(program);
        unload();
        return false;
    }
    
    //done linking, detach the shaders now
    detachAndUnloadShaders(shaders, program);
    
    return true;
}

void ProgramLinker::use()
{
    if (vaoID == 0) {
        glGenVertexArrays(1, &vaoID);
    }

    glBindVertexArray(vaoID);
    glUseProgram(program);
    for (int i = 0; i < numAttributes; ++i) {
        //BUG! glEnableVertexAttribArray causes GL ERROR CODE 1282
        //(invalid operation) on OS X
        glEnableVertexAttribArray(i);
    }
}

void ProgramLinker::unload()
{
    if (program != 0) {
        glDeleteProgram(program);
    }

    program = 0;
}

void ProgramLinker::unuse()
{
    for (int i = 0; i < numAttributes; ++i) {
        glDisableVertexAttribArray(i);
    }
    glBindVertexArray(0);
    glUseProgram(0);
}
