uniform mat4 view;
uniform mat4 world;

in vec2 a_uv1;
in vec4 a_position;
 
out vec2 v_uv1;
 
void main()
{
    gl_Position = view * world * a_position;
    v_uv1 = a_uv1;
 }