in vec2 v_uv1;

uniform sampler2D texture1;
uniform sampler2D texture2;
uniform float time;

out vec4 PixelColor;

void main()
{
    PixelColor = texture(texture1, v_uv1) * texture(texture2, v_uv1 + vec2(0.4,0.1) * sin(time));
}
