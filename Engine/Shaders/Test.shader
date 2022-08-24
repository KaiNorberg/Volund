#Shader vertex
#version FILL

layout(location = 0) in vec3 vertex_position;

out vec3 vs_position;

void main()
{
    vs_position = vertex_position;
    gl_Position = vec4(vertex_position, 1.0f);
};

#Shader fragment
#version FILL

in vec3 vs_position;

out vec4 FragColor;

void main()
{
    FragColor = vec4(vs_position + 0.5f, 1.0f);
}