uniform sampler2D tex;

in vec2 v_uv1;
in vec4 v_color;

out vec4 pixelColour;

void main()
{
    //pixelColour = v_color / 255.0f;
    pixelColour = texture(tex, v_uv1);
}