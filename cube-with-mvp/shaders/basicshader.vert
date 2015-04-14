#version 330

layout(location=0) in vec4 position;
layout(location=1) in vec3 color;
uniform mat4 modelViewProjection;

out vec3 fragmentColor;

void main()
{
    fragmentColor = color;
    gl_Position = modelViewProjection * position;
}
