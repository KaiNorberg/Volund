#VOLUND_SHADER_TYPE VERTEX
#version 460

layout(location = 0) in vec3 VertexPosition;
layout(location = 1) in vec2 VertexTextureCoord;
layout(location = 2) in vec3 VertexNormal;

out vec3 FragPos;
out vec2 FragTexCoord;
out vec3 FragNormal;

layout(std140, binding = 0) uniform Camera
{
	mat4 ViewMatrix;
	mat4 ProjectionMatrix;
};

uniform mat4 _ModelMatrix;

void main()
{
    FragPos = (_ModelMatrix * vec4(VertexPosition, 1.0)).xyz;
    FragTexCoord = VertexTextureCoord;
    FragNormal = normalize(mat3(_ModelMatrix) * VertexNormal);
    gl_Position = ProjectionMatrix * ViewMatrix * vec4(FragPos, 1.0f);
}

#VOLUND_SHADER_TYPE FRAGMENT
#version 460

in vec3 FragPos;
in vec2 FragTexCoord;
in vec3 FragNormal;

#VOLUND_MATERIAL_START

uniform int entityId;

#VOLUND_MATERIAL_END

layout(location = 0) out vec4 FragColor;

void main() 
{
    FragColor = vec4(1.0f, 0, 1.0f, 1.0f);
}