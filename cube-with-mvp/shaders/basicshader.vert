#version 330

layout(location=0) in vec4 position;
uniform mat4 modelViewProjection;

void main()
{
    gl_Position = modelViewProjection * position;
}
