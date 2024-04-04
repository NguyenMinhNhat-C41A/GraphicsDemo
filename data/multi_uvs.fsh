in vec2 v_uv1;
in vec2 v_uv2;

uniform sampler2D texture1;
uniform sampler2D texture2;

out vec4 PixelColor;

void main()
{
    PixelColor = texture(texture1, v_uv1) * 
                 texture(texture2, v_uv2);
}

