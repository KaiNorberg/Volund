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
	mat4 ViewMatrix;
	mat4 ProjectionMatrix;

	vec3 Position;

    int LayerMask;
};

out vec2 Coord;

uniform mat4 _ModelMatrix;

void main()
{    
    Coord = VertexTextureCoord;

    FragPosition = (_ModelMatrix * vec4(VertexPosition, 1.0)).xyz;
    FragTextureCoord = VertexTextureCoord;
    FragNormal = normalize(mat3(_ModelMatrix) * VertexNormal);
    gl_Position = ViewProjMatrix * vec4(FragPosition, 1.0f);
};

#VOLUND_SHADER_TYPE FRAGMENT
#version 460

in vec2 Coord;

#VOLUND_MATERIAL_START

uniform int MaxIterations;
uniform vec2 Position;
uniform float Scale;
uniform int Julia;
uniform float JuliaC;

#VOLUND_MATERIAL_END

layout(location = 0) out vec4 FragColor;

vec3 spectral_color(float l)        // RGB <0,1> <- lambda l <400,700> [nm]
{
    float t; 
    vec3 c = vec3(0.0,0.0,0.0);

    if ((l>=400.0)&&(l<410.0)) { t=(l-400.0)/(410.0-400.0); c.r=    +(0.33*t)-(0.20*t*t); }
    else if ((l>=410.0)&&(l<475.0)) { t=(l-410.0)/(475.0-410.0); c.r=0.14         -(0.13*t*t); }
    else if ((l>=545.0)&&(l<595.0)) { t=(l-545.0)/(595.0-545.0); c.r=    +(1.98*t)-(     t*t); }
    else if ((l>=595.0)&&(l<650.0)) { t=(l-595.0)/(650.0-595.0); c.r=0.98+(0.06*t)-(0.40*t*t); }
    else if ((l>=650.0)&&(l<700.0)) { t=(l-650.0)/(700.0-650.0); c.r=0.65-(0.84*t)+(0.20*t*t); }
    
    if ((l>=415.0)&&(l<475.0)) { t=(l-415.0)/(475.0-415.0); c.g=             +(0.80*t*t); }
    else if ((l>=475.0)&&(l<590.0)) { t=(l-475.0)/(590.0-475.0); c.g=0.8 +(0.76*t)-(0.80*t*t); }
    else if ((l>=585.0)&&(l<639.0)) { t=(l-585.0)/(639.0-585.0); c.g=0.84-(0.84*t); }
    
    if ((l>=400.0)&&(l<475.0)) { t=(l-400.0)/(475.0-400.0); c.b=    +(2.20*t)-(1.50*t*t); }
    else if ((l>=475.0)&&(l<560.0)) { t=(l-475.0)/(560.0-475.0); c.b=0.7 -(     t)+(0.30*t*t); }

    return c;
}

int ComputeMandelbrot(dvec2 C, int Iterations, float Threshold)
{
    dvec2 Z = dvec2(0.0);

    for (int i = 0; i < Iterations; i++)
    {
        dvec2 SquareZ;
        SquareZ.x = Z.x * Z.x - Z.y * Z.y;
        SquareZ.y = 2 * Z.x * Z.y;
        Z = SquareZ + C;

        if (length(SquareZ) > Threshold)
        {
            return i;
        }
    }

    return Iterations;
}

int ComputeJulia(dvec2 C, int Iterations, float Threshold)
{
    dvec2 Z = C;

    C = dvec2(JuliaC);

    for (int i = 0; i < Iterations; i++)
    {
        dvec2 SquareZ;
        SquareZ.x = Z.x * Z.x - Z.y * Z.y;
        SquareZ.y = 2 * Z.x * Z.y;
        Z = SquareZ + C;

        if (length(SquareZ) > Threshold)
        {
            return i;
        }
    }

    return Iterations;
}

void main()
{
    dvec2 NewCoord = (Coord * 2.0 - 1.0) * 20.0;
    NewCoord -= Position / Scale;
    NewCoord *= Scale;

    float Iter = 0;

    if (Julia == 1)
    {
        Iter = ComputeJulia(NewCoord, MaxIterations, 4);
    }
    else
    {
        Iter = ComputeMandelbrot(NewCoord, MaxIterations, 4);
    }

    float Q = float(Iter) / float(MaxIterations);
    Q = pow(Q, 0.2);
    vec3 PixelColor = spectral_color(500.0 + (300.0 * Q));

    FragColor = vec4(PixelColor, 1.0f);
}