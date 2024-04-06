in vec4 v_color;

out vec4 pixelColour;

void main()
{
    pixelColour = v_color / 255.0f;
}