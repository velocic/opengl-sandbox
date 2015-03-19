#version 330

layout(location=0) in vec2 vertexPosition;
layout(location=1) in vec4 vertexColor;

out vec4 fragmentColor;

void main()
{
    gl_Position.xy = vertexPosition;
    gl_Position.z = 0.0;
    gl_Position.w = 1.0;

    fragmentColor = vertexColor;
}
