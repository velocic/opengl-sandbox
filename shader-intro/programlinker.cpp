#include <programlinker.h>

//TODO: Add addAttribute function for adding attributes to the program. keep a count of them.
//for reference, gfx tutorial 8 @ 30:00

ProgramLinker::~ProgramLinker()
{
    unload();
}

void ProgramLinker::compileAndAttachShaders(std::vector<Shader> &shaders, const GLuint &program)
{
    //TODO: we should abort if any shader fails to compile
    for (Shader shader : shaders) {
        shader.compile();
        glAttachShader(program, shader.getOGLHandle());
    }
}

void ProgramLinker::detachAndUnloadShaders(std::vector<Shader> &shaders, const GLuint &program)
{
    for (Shader shader : shaders) {
        glDetachShader(program, shader.getOGLHandle());
        shader.unload();
    }
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

GLuint ProgramLinker::getProgram()
{
    return program;
}

bool ProgramLinker::link()
{
    bool linkedSuccessfully = true;
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
        linkedSuccessfully = false;
    }
    
    //done linking, detach the shaders now
    detachAndUnloadShaders(shaders, program);
    
    return linkedSuccessfully;
}

void ProgramLinker::unload()
{
    detachAndUnloadShaders(shaders, program);

    if (program != 0) {
        glDeleteProgram(program);
    }

    program = 0;
}
