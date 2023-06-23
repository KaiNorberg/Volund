#VOLUND_SHADER_TYPE VERTEX
#version 460

uniform mat4 ViewMatrix;
uniform mat4 ProjectionMatrix;

layout(location = 1) out vec3 NearPoint;
layout(location = 2) out vec3 FarPoint;

vec3 UnprojectPoint(vec3 p)
{
    mat4 viewInv = inverse(ViewMatrix);
    mat4 projInv = inverse(ProjectionMatrix);
    vec4 unprojectedPoint = viewInv * projInv * vec4(p, 1.0);
    return unprojectedPoint.xyz / unprojectedPoint.w;
}

void main()
{
    float x = float(((uint(gl_VertexID)+2u) / 3u) % 2u);
    float y = float(((uint(gl_VertexID)+1u) / 3u) % 2u);
    vec3 p = vec3(-1.0f + x * 2.0f, -1.0f + y * 2.0f, 0.0f);

    NearPoint = UnprojectPoint(vec3(p.xy, 0.0)).xyz;
    FarPoint = UnprojectPoint(vec3(p.xy, 1.0)).xyz;

    gl_Position = vec4(p, 1.0f);
}

#VOLUND_SHADER_TYPE FRAGMENT
#version 460

uniform mat4 ViewMatrix;
uniform mat4 ProjectionMatrix;
uniform float CameraDistance;

layout(location = 1) in vec3 NearPoint;
layout(location = 2) in vec3 FarPoint;

layout(location = 0) out vec4 FragColor;

vec4 Grid(vec3 worldPos, float scale)
{
    vec2 coord = worldPos.xz / scale;
    vec2 derivative = fwidth(coord);
    vec2 grid = abs(fract(coord - 0.5) - 0.5) / derivative;
    float line = min(grid.x, grid.y);

    float alpha = 1.0f - min(line, 1.0);

    float minimumz = min(derivative.y, 1);
    float minimumx = min(derivative.x, 1);

    if (abs(worldPos.z) < minimumz)
    {
        return vec4(40.0 / 255.0, 140.0 / 255.0, 244.0 / 255.0, alpha);
    }
    else if (abs(worldPos.x) < minimumx)
    {
        return vec4(244.0 / 255.0, 51.0 / 255.0, 81.0 / 255.0, alpha);
    }
    else
    {
        return vec4(73.0 / 255.0, 75.0 / 255.0, 77.0 / 255.0, alpha);
    }
}

float ComputeDepth(vec3 pos)
{
    vec4 clip_space_pos = ProjectionMatrix * ViewMatrix * vec4(pos, 1.0);
    return ((clip_space_pos.z / clip_space_pos.w) + 1.0f) * 0.5f;
}

vec3 GetCameraPosition()
{
    mat4 inverseViewMatrix = inverse(ViewMatrix);

    vec3 cameraPosition = vec3(inverseViewMatrix[3][0], inverseViewMatrix[3][1], inverseViewMatrix[3][2]);

    return cameraPosition;
}

void main()
{
    float t = -NearPoint.y / (FarPoint.y - NearPoint.y);

    vec3 worldPos = NearPoint + t * (FarPoint - NearPoint);

    vec3 cameraPos = GetCameraPosition();

    const float maxDistance = 75.0f;
    float disatance = length(cameraPos - worldPos);

    vec4 color = Grid(worldPos, 2.5f) * max(0, 1.0f - (disatance / maxDistance));

    gl_FragDepth = ComputeDepth(worldPos);
    FragColor = color;
}
