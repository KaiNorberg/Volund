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

const float PI = 3.14159265359;

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
uniform vec3 Albedo;
uniform float Metalness;
uniform float Roughness;

layout(location = 0) out vec4 FragColor;

float DistributionGGX(vec3 N, vec3 H, float roughness)
{
    float a      = roughness*roughness;
    float a2     = a*a;
    float NdotH  = max(dot(N, H), 0.0);
    float NdotH2 = NdotH*NdotH;
	
    float num   = a2;
    float denom = (NdotH2 * (a2 - 1.0) + 1.0);
    denom = PI * denom * denom;
	
    return num / denom;
}

float GeometrySchlickGGX(float NdotV, float roughness)
{
    float r = (roughness + 1.0);
    float k = (r*r) / 8.0;

    float num   = NdotV;
    float denom = NdotV * (1.0 - k) + k;
	
    return num / denom;
}

float GeometrySmith(vec3 N, vec3 V, vec3 L, float roughness)
{
    float NdotV = max(dot(N, V), 0.0);
    float NdotL = max(dot(N, L), 0.0);
    float ggx2  = GeometrySchlickGGX(NdotV, roughness);
    float ggx1  = GeometrySchlickGGX(NdotL, roughness);
	
    return ggx1 * ggx2;
}

vec3 fresnelSchlick(float cosTheta, vec3 F0)
{
    return F0 + (1.0 - F0) * pow(clamp(1.0 - cosTheta, 0.0, 1.0), 5.0);
}  

void main()
{
    vec3 V = normalize(EyePosition - FragPosition);

    vec3 F0 = vec3(0.04); 
    F0 = mix(F0, Albedo, Metalness);
	           
    // reflectance equation
    vec3 Lo = vec3(0.0);
    for(int i = 0; i < LightAmount; ++i) 
    {
        // calculate per-light radiance
        vec3 L = normalize(LightPositions[i] - FragPosition);
        vec3 H = normalize(V + L);
        float distance = length(LightPositions[i] - FragPosition);
        float attenuation = 1.0 / (distance * distance);
        vec3 radiance = LightColors[i] * attenuation;        
        
        // cook-torrance brdf
        float NDF = DistributionGGX(FragNormal, H, Roughness);        
        float G = GeometrySmith(FragNormal, V, L, Roughness);      
        vec3 F = fresnelSchlick(max(dot(H, V), 0.0), F0);       
        
        vec3 kS = F;
        vec3 kD = vec3(1.0) - kS;
        kD *= 1.0 - Metalness;	  
        
        vec3 numerator = NDF * G * F;
        float denominator = 4.0 * max(dot(FragNormal, V), 0.0) * max(dot(FragNormal, L), 0.0) + 0.0001;
        vec3 specular = numerator / denominator;  
            
        // add to outgoing radiance Lo
        float NdotL = max(dot(FragNormal, L), 0.0);                
        Lo += (kD * Albedo / PI + specular) * radiance * NdotL; 
    }   
  
    //vec3 ambient = vec3(0.03) * Albedo;
    vec3 ambient = vec3(0.0);
    vec3 color = ambient + Lo;
   
    FragColor = vec4(color, 1.0);
}
)====="