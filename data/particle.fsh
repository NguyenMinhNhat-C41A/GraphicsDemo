uniform sampler2D tex;

in vec2 v_uv1;
in vec4 v_color;

out vec4 pixelColour;

void main()
{
     vec4 finalColour = texture(tex, v_uv1);
     finalColour.a = v_color.a;
     pixelColour = finalColour;
}