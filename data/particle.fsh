uniform sampler2D tex;

in vec2 v_uv1;
 
out vec4 pixelColour;

void main()
{
     pixelColour = texture(tex, v_uv1);
}