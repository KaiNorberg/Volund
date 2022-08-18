////////////////////////////////////////////////////////////
///
/// This shader will draw a object.
/// The shader will receive the following:
/// 
/// The Material of the object.
/// The ModelMatrix of the object.
///	The ViewMatrix of the camera used to render the object.
///	The ProjectionMatrix of the camera used to render the object.
///
////////////////////////////////////////////////////////////

#Shader vertex
#version FILL

layout(location = 0) in vec3 vertex_position;
layout(location = 1) in vec2 vertex_texcoord;
layout(location = 2) in vec3 vertex_normal;

out vec3 vs_position;
out vec2 vs_texcoord;
out vec3 vs_normal;

uniform mat4 ModelMatrix;
uniform mat4 ViewMatrix;
uniform mat4 ProjectionMatrix;

void main()
{
    vs_position = vec4(ModelMatrix * vec4(vertex_position, 1.0f)).xyz;
    vs_texcoord = vec2(vertex_texcoord.x, -vertex_texcoord.y);
    vs_normal = normalize(mat3(ModelMatrix) * vertex_normal);

    gl_Position = ProjectionMatrix * ViewMatrix * ModelMatrix * vec4(vertex_position, 1.0f);
};

#Shader fragment
#version FILL

in vec3 vs_position;
in vec2 vs_texcoord;
in vec3 vs_normal;

out vec4 FragColor;

struct material
{
    vec3 Albedo;
    float Metallic;
    float Roughness;
    float Emission;
    float Lighting;
    bool UseAlbedo;
    sampler2D TextureAlbedo;
    bool UseMetallic;
    sampler2D TextureMetallic;
    bool UseRoughness;
    sampler2D TextureRoughness;
    bool UseEmission;
    sampler2D TextureEmission;
};
uniform material Material;

struct PointLight
{
    vec3 Position;
    vec3 Color;
}; 
uniform PointLight PointLights[1000];
uniform int AmountOfPointLights;

struct DirectionalLight
{
    vec3 Position;
    vec3 Color;
    bool ShadowsEnabled;
    sampler2D ShadowMap;
    mat4 ShadowMatrix;
};
uniform DirectionalLight DirectionalLights[5];
uniform int AmountOfDirectionalLights;

uniform vec3 CameraPos;

void main()
{  
    FragColor = vec4(1.0f);
}