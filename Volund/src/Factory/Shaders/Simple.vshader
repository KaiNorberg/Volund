R"=====(
#VOLUND_SHADER_TYPE VERTEX
#version 460

layout(location = 0) in vec3 Vertex_Position;
layout(location = 1) in vec2 Vertex_TextureCoord;
layout(location = 2) in vec3 Vertex_Normal;

out vec3 Position;
out vec2 TextureCoord;
out vec3 Normal;

layout(std140, binding = 0) uniform Camera
{
    mat4 ViewProjMatrix;
    vec3 EyePosition;
};

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

in vec3 Position;
in vec2 TextureCoord;
in vec3 Normal;

layout(std140, binding = 0) uniform Camera
{
    mat4 ViewProjMatrix;
    vec3 EyePosition;
};

layout(std140, binding = 1) uniform LightsUniform
{
    int LightAmount;
    vec3 LightPositions[64];    
    vec3 LightColors[64];
};

//Material Uniforms
uniform vec3 Color;

layout(location = 0) out vec4 FragColor;

void main()
{
    vec3 Result;
    for (int i = 0; i < LightAmount; i++)
    {
        vec3 LightDir = normalize(LightPositions[i] - Position);
        float Diffuse = max(dot(Normal, LightDir), 0.0);
        vec3 ViewDir = normalize(EyePosition - Position);
        vec3 ReflectDir = reflect(-LightDir, Normal);
        float Specular = pow(max(dot(ViewDir, ReflectDir), 0.0), 32);
        Result += (Diffuse + Specular) * LightColors[i] * Color;
    }
    FragColor = vec4(Result, 1.0f);
}
)====="