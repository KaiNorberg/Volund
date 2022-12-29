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
    Position = (_ModelMatrix * vec4(Vertex_Position, 1.0)).xyz;
    TextureCoord = Vertex_TextureCoord;
    Normal = normalize(mat3(_ModelMatrix) * Vertex_Normal);
    gl_Position = ViewProjMatrix * vec4(Position, 1.0f);
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
uniform float AmbientLighting;
uniform vec3 Color;
uniform float ColorTextureMix;
uniform sampler2D ColorTexture;

layout(location = 0) out vec4 FragColor;

void main()
{
    vec3 TextureColor = texture(ColorTexture, TextureCoord).rgb;
    vec3 FinalColor = mix(Color, TextureColor, ColorTextureMix).rgb;

    vec3 Result = FinalColor * AmbientLighting;
    for (int i = 0; i < LightAmount; i++)
    {  
        vec3 L = normalize(LightPositions[i] - Position);

        // Lambert's cosine law
        float Lambertian = max(dot(Normal, L), 0.0);
        if (Lambertian > 0.0)
        {
            vec3 R = reflect(-L, Normal);
            vec3 V = normalize(EyePosition - Position);

            float SpecAngle = max(dot(R, V), 0.0);
            float Specular = pow(SpecAngle, 32.0f);

            Result += vec3(Lambertian + Specular) * LightColors[i] * FinalColor;
        }
    }

    FragColor = vec4(Result, 1.0f);
}
)====="