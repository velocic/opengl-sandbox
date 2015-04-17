#version 330

in vec2 UV;
out vec3 color;

/* Values that stay constant for the whole mesh */
uniform sampler2D myTextureSampler;

void main()
{
    //Output color = color of the texture at the specified UV
    color = texture(myTextureSampler, UV).rgb;
}
