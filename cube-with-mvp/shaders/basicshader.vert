#version 330

layout(location=0) in vec4 position;
layout(location=1) in vec2 vertexUV;
uniform mat4 modelViewProjection;

out vec2 UV;

void main()
{
    gl_Position = modelViewProjection * position;
    UV = vertexUV;
}
