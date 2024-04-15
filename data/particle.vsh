uniform mat4 proj_view;
uniform mat4 world;

in vec2 a_uv1;
in vec4 a_color;
in vec4 a_position;
 
out vec2 v_uv1;
out vec4 v_color;
 
void main()
{
    gl_Position = proj_view * world * a_position;
    v_uv1 = a_uv1;
    v_color = a_color / 256;
 }