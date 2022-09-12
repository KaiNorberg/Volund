#VOLUND_SHADER_TYPE VERTEX
#version 460

layout(location = 0) in vec3 Vertex_Position;
layout(location = 1) in vec2 Vertex_TextureCoord;
layout(location = 2) in vec3 Vertex_Normal;

out vec3 Position;
out vec2 TextureCoord;
out vec3 Normal;

uniform mat4 ViewProjMatrix;
uniform mat4 ModelMatrix;

void main()
{
    Position = vec3(ModelMatrix * vec4(Vertex_Position, 1.0));
    TextureCoord = Vertex_TextureCoord;
    Normal = Vertex_Normal;
    gl_Position = ViewProjMatrix * ModelMatrix * vec4(Vertex_Position, 1.0f);
};

#VOLUND_SHADER_TYPE FRAGMENT
#version 460

struct PointLight
{
    vec3 Color;
    vec3 Position;
};
uniform int PointLightAmount;
uniform PointLight PointLights[64];

uniform vec3 EyePosition;

in vec3 Position;
in vec2 TextureCoord;
in vec3 Normal;

out vec4 FragColor;

void main()
{
    vec3 Result;
    for (int i = 0; i < PointLightAmount; i++)
    { 
        vec3 LightDir = normalize(PointLights[i].Position - Position); 
        float Diffuse = max(dot(Normal, LightDir), 0.0);

        vec3 ViewDir = normalize(EyePosition - Position);
        vec3 ReflectDir = reflect(-LightDir, Normal);

        float Specular = pow(max(dot(ViewDir, ReflectDir), 0.0), 32);

        Result += (Diffuse + Specular) * PointLights[i].Color;
    }

    FragColor = vec4(Result, 1.0f);
}