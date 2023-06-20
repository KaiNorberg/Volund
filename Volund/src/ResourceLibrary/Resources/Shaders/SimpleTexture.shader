R"=====(
#VOLUND_SHADER_TYPE VERTEX
#version 460

layout(location = 0) in vec3 VertexPosition;
layout(location = 1) in vec2 VertexTextureCoord;
layout(location = 2) in vec3 VertexNormal;

out vec3 fragPos;
out vec2 fragTexCoord;
out vec3 fragNormal;

layout(std140, binding = 0) uniform Camera
{
	mat4 ViewMatrix;
	mat4 ProjectionMatrix;
};

uniform mat4 _ModelMatrix;

void main()
{
    fragPos = (_ModelMatrix * vec4(VertexPosition, 1.0)).xyz;
    fragTexCoord = VertexTextureCoord;
    fragNormal = normalize(mat3(_ModelMatrix) * VertexNormal);
    gl_Position = ProjectionMatrix * ViewMatrix * vec4(fragPos, 1.0f);
}

#VOLUND_SHADER_TYPE FRAGMENT
#version 460

in vec3 fragPos;
in vec2 fragTexCoord;
in vec3 fragNormal;

layout(std140, binding = 0) uniform Camera
{
	mat4 ViewMatrix;
	mat4 ProjectionMatrix;
};

layout(std140, binding = 1) uniform Lights
{
	int LightAmount;
    vec4 LightColors[64];
    vec4 LightPositions[64];
};

#VOLUND_MATERIAL_START

uniform vec3 Ambient;
uniform sampler2D ColorTexture;

#VOLUND_MATERIAL_END

layout(location = 0) out vec4 FragColor;

vec3 GetCameraPosition() 
{
    mat4 inverseViewMatrix = inverse(ViewMatrix);
    
    vec3 cameraPosition = vec3(inverseViewMatrix[3][0], inverseViewMatrix[3][1], inverseViewMatrix[3][2]);
    
    return cameraPosition;
}

void main()
{    
    vec3 cameraPosition = GetCameraPosition();

    vec3 color = texture(ColorTexture, fragTexCoord).rgb;

    vec3 result = color * Ambient;
    for (int i = 0; i < LightAmount; i++)
    {  
        vec3 l = normalize(LightPositions[i].xyz - fragPos);

        float lambertian = max(dot(fragNormal, l), 0.0);
        if (lambertian > 0.0)
        {
            vec3 r = reflect(-l, fragNormal);
            vec3 v = normalize(cameraPosition - fragPos);
            vec3 halfV = normalize(l + v);

            float specular = pow(max(dot(fragNormal, halfV), 0.0), 32.0f);

            result += vec3(lambertian + specular) * LightColors[i].xyz * color;
        }
    }

    FragColor = vec4(result, 1.0f);
}
)====="