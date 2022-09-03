#VOLUND_SHADER_TYPE VERTEX
#version 460

layout(location = 0) in vec3 Vertex_Position;
layout(location = 1) in vec2 Vertex_TextureCoords;
layout(location = 2) in vec3 Vertex_Normals;

out vec3 Position;

uniform mat4 ViewProjMatrix;
uniform mat4 ModelMatrix;

void main()
{
    Position = Vertex_Position;
    gl_Position = ViewProjMatrix * ModelMatrix * vec4(Vertex_Position, 1.0f);
};

#VOLUND_SHADER_TYPE FRAGMENT
#version 460

in vec3 Position;

out vec4 FragColor;

void main()
{
    FragColor = vec4(normalize(Position), 1.0f);
}