uniform mat4 view;
uniform mat4 world;

in vec2 a_uv1;
in vec4 a_position;
in vec4 a_color;

out vec2 v_uv1;
out vec4 v_color;

void main()
{
    gl_Position = view * world * a_position;
    v_color = a_color;
}