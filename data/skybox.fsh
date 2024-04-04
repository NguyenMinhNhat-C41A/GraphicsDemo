out vec4 PixelColor;

in vec3 TexCoords;

uniform samplerCube skyboxTexture;

void main()
{    
    PixelColor = texture(skyboxTexture, TexCoords);
}