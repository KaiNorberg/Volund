#VOLUND_SHADER_TYPE VERTEX
#version 460

layout(location = 0) in vec3 Vertex_Position;
layout(location = 1) in vec2 Vertex_TextureCoord;
layout(location = 2) in vec3 Vertex_Normal;

layout(std140, binding = 0) uniform Camera
{
    mat4 ViewProjMatrix;
    vec3 EyePosition;
};

out vec2 Coord;

uniform mat4 _ModelMatrix;

void main()
{
    Coord = Vertex_TextureCoord;
    gl_Position = ViewProjMatrix * vec4(Vertex_Position, 1.0f);
};

#VOLUND_SHADER_TYPE FRAGMENT
#version 460

in vec2 Coord;

//Material Uniforms
uniform vec3 Color;

layout(location = 0) out vec4 FragColor;

int ComputeMandelbrot(vec2 C, int Iterations, float Threshold)
{
    vec2 Z = vec2(0.0f);

    for (int i = 0; i < Iterations; i++)
    {
        vec2 SquareZ;
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
    vec2 NewCoord = (Coord * 2.0f - 1.0f) * 2.0f;
    NewCoord.x -= 0.5f;

    const int Iterations = 35;

    float Gradient = float(ComputeMandelbrot(NewCoord, Iterations, 4)) / float(Iterations);

    FragColor = vec4(Color * Gradient, 1.0f);
}