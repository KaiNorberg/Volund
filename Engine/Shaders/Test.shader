#VOLUND_SHADER_TYPE VERTEX
#VOLUND_SHADER_VERSION

layout(location = 0) in vec3 vertex_position;
layout(location = 1) in vec4 vertex_color;

out vec3 vs_position;
out vec4 vs_color;

void main()
{
    vs_position = vertex_position;
    vs_color = vertex_color;
    gl_Position = vec4(vertex_position, 1.0f);
};

#VOLUND_SHADER_TYPE FRAGMENT
#VOLUND_SHADER_VERSION

in vec3 vs_position;
in vec4 vs_color;

out vec4 FragColor;

void main()
{
    FragColor = vs_color;
}