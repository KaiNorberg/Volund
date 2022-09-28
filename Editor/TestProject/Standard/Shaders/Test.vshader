#VOLUND_SHADER_TYPE VERTEX
#version 460

layout(location = 0) in vec3 Vertex_Position;
layout(location = 1) in vec2 Vertex_TextureCoord;
layout(location = 2) in vec3 Vertex_Normal;

out vec3 Position;
out vec2 TextureCoord;
out vec3 Normal;

layout(packed, binding = 0) uniform Camera
{
    mat4 ViewProjMatrix;
    vec3 EyePosition;
};

//uniform mat4 _ViewProjMatrix;
uniform mat4 _ModelMatrix;

void main()
{
    Position = vec3(_ModelMatrix * vec4(Vertex_Position, 1.0));
    TextureCoord = Vertex_TextureCoord;
    Normal = Vertex_Normal;
    gl_Position = ViewProjMatrix * _ModelMatrix * vec4(Vertex_Position, 1.0f);
};

#VOLUND_SHADER_TYPE FRAGMENT
#version 460

layout(packed, binding = 0) uniform Camera
{
    mat4 ViewProjMatrix; 
    vec3 EyePosition;
};

//Material Uniforms
uniform vec3 Color;

in vec3 Position;
in vec2 TextureCoord;
in vec3 Normal;

layout(location = 0) out vec4 FragColor;

void main()
{
    FragColor = vec4(EyePosition, 1.0f);
}