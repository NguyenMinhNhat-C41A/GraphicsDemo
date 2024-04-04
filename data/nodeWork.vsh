uniform mat4 projection_view;
uniform mat4 world;

in vec4 a_position;


void main() {
    gl_Position = projection_view * world * a_position;
}