R"=====(
#VOLUND_SHADER_TYPE VERTEX
#version 460

layout(location = 0) in vec3 VertexPosition;
layout(location = 1) in vec2 VertexTextureCoord;
layout(location = 2) in vec3 VertexNormal;

out vec3 FragPosition;
out vec2 FragTextureCoord;
out vec3 FragNormal;

layout(std140, binding = 0) uniform Camera
{
    mat4 ViewProjMatrix;
    vec3 EyePosition;
};

uniform mat4 _ModelMatrix;

void main()
{
    FragPosition = (_ModelMatrix * vec4(VertexPosition, 1.0)).xyz;
    FragTextureCoord = VertexTextureCoord;
    FragNormal = normalize(mat3(_ModelMatrix) * VertexNormal);
    gl_Position = ViewProjMatrix * vec4(FragPosition, 1.0f);
};

#VOLUND_SHADER_TYPE FRAGMENT
#version 460

in vec3 FragPosition;
in vec2 FragTextureCoord;
in vec3 FragNormal;

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
uniform vec3 AmbientLighting;
uniform vec3 Color;

layout(location = 0) out vec4 FragColor;

void main()
{
    vec3 Result = Color * AmbientLighting;
    for (int i = 0; i < LightAmount; i++)
    {  
        vec3 L = normalize(LightPositions[i] - FragPosition);

        // Lambert's cosine law
        float Lambertian = max(dot(FragNormal, L), 0.0);
        if (Lambertian > 0.0)
        {
            vec3 R = reflect(-L, FragNormal);
            vec3 V = normalize(EyePosition - FragPosition);
            vec3 HalfV = normalize(L + V);

            float Specular = pow(max(dot(FragNormal, HalfV), 0.0), 32.0f);

            Result += vec3(Lambertian + Specular) * LightColors[i] * Color;
        }
    }

    FragColor = vec4(Result, 1.0f);
}
)====="