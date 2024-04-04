uniform mat4 view;
uniform mat4 world;
in vec4 a_position;
void main()
{
    gl_Position = view * world * a_position;
}