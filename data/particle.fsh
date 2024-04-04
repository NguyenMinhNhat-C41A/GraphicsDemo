uniform vec4 colour;

out vec4 pixelColour;

void main()
{
    pixelColour = colour / 255.0f;
}