R"=====(
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
uniform sampler2D AlbedoTexture;
uniform float Roughness;
uniform float Metallic;

#VOLUND_MATERIAL_END

const float PI = 3.14159265359;

layout(location = 0) out vec4 FragColor;

vec3 GetCameraPosition() 
{
    mat4 inverseViewMatrix = inverse(ViewMatrix);
    
    vec3 cameraPosition = vec3(inverseViewMatrix[3][0], inverseViewMatrix[3][1], inverseViewMatrix[3][2]);
    
    return cameraPosition;
}

float DistributionGGX(vec3 N, vec3 H, float Roughness)
{
    float a      = Roughness*Roughness;
    float a2     = a*a;
    float NdotH  = max(dot(N, H), 0.0);
    float NdotH2 = NdotH*NdotH;
	
    float num   = a2;
    float denom = (NdotH2 * (a2 - 1.0) + 1.0);
    denom = PI * denom * denom;
	
    return num / denom;
}

float GeometrySchlickGGX(float NdotV, float Roughness)
{
    float r = (Roughness + 1.0);
    float k = (r*r) / 8.0;

    float num   = NdotV;
    float denom = NdotV * (1.0 - k) + k;
	
    return num / denom;
}

float GeometrySmith(vec3 N, vec3 V, vec3 L, float Roughness)
{
    float NdotV = max(dot(N, V), 0.0);
    float NdotL = max(dot(N, L), 0.0);
    float ggx2  = GeometrySchlickGGX(NdotV, Roughness);
    float ggx1  = GeometrySchlickGGX(NdotL, Roughness);
	
    return ggx1 * ggx2;
}

vec3 FresnelSchlick(float cosTheta, vec3 F0)
{
    return F0 + (1.0 - F0) * pow(clamp(1.0 - cosTheta, 0.0, 1.0), 5.0);
}  

void main()
{		        
    vec3 Albedo = texture(AlbedoTexture, FragTexCoord).rgb;

    vec3 camPos = GetCameraPosition();

    vec3 N = normalize(FragNormal);
    vec3 V = normalize(camPos - FragPos);

    vec3 F0 = vec3(0.04); 
    F0 = mix(F0, Albedo, Metallic);
	           
    // reflectance equation
    vec3 Lo = vec3(0.0);
    for(int i = 0; i < LightAmount; ++i) 
    {
        // calculate per-light radiance
        vec3 L = normalize(LightPositions[i].xyz - FragPos);
        vec3 H = normalize(V + L);
        float distance    = length(LightPositions[i].xyz - FragPos);
        float attenuation = 1.0 / (distance * distance);
        vec3 radiance     = LightColors[i].xyz * attenuation;        
        
        // cook-torrance brdf
        float NDF = DistributionGGX(N, H, Roughness);        
        float G   = GeometrySmith(N, V, L, Roughness);      
        vec3 F    = FresnelSchlick(max(dot(H, V), 0.0), F0);       
        
        vec3 kS = F;
        vec3 kD = vec3(1.0) - kS;
        kD *= 1.0 - Metallic;	  
        
        vec3 numerator    = NDF * G * F;
        float denominator = 4.0 * max(dot(N, V), 0.0) * max(dot(N, L), 0.0) + 0.0001;
        vec3 specular     = numerator / denominator;  
            
        // add to outgoing radiance Lo
        float NdotL = max(dot(N, L), 0.0);                
        Lo += (kD * Albedo / PI + specular) * radiance * NdotL; 
    }   
  
    vec3 color = Ambient * Albedo + Lo;
	
    //TODO: Move gamma to post processing
    color = color / (color + vec3(1.0));
    color = pow(color, vec3(1.0/2.2));  
   
    FragColor = vec4(color, 1.0);
}  
)====="