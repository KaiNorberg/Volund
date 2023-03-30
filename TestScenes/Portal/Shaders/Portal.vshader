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

in vec4 gl_FragCoord; 

in vec3 FragPosition;
in vec2 FragTextureCoord;
in vec3 FragNormal;

layout(std140, binding = 0) uniform Camera
{    
    mat4 ViewProjMatrix;
    vec3 EyePosition;
};

//Material Uniforms
uniform sampler2D ColorTexture;
uniform vec2 ScreenSize;

layout(location = 0) out vec4 FragColor;

void main()
{
    vec2 ScreenPos = ((gl_FragCoord.xy) / ScreenSize);
    FragColor = texture(ColorTexture, (ScreenPos));
    //FragColor = vec4(ScreenPos, 0.0, 1.0);
}