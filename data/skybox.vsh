in vec4 a_position;

out vec3 TexCoords;

uniform mat4 projection_view;

void main()
{
    TexCoords = vec3(a_position.x, a_position.y, a_position.z);
    gl_Position = projection_view * vec4(a_position.x, a_position.y, a_position.z, 1.0);
} 