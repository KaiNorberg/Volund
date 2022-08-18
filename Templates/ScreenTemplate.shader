////////////////////////////////////////////////////////////
///
/// This shader will draw a quad over the entire window.
/// The correct usage looks as following:
/// 
///	Engine.MainFramebuffer.BindFramebuffer();
///	"Shader".DrawArrays(BUFFER_COPY_VERTICE_AMOUNT);
///
////////////////////////////////////////////////////////////

#Shader vertex
#version FILL

out vec2 TexCoords;

void main()
{
    float x = float(((uint(gl_VertexID)+2u) / 3u) % 2u);
    float y = float(((uint(gl_VertexID)+1u) / 3u) % 2u);

    gl_Position = vec4(-1.0f + x * 2.0f, -1.0f + y * 2.0f, 0.0f, 1.0f);
    TexCoords = vec2(x, y);
}

#Shader fragment
#version FILL

out vec4 FragColor;

in vec2 TexCoords;

void main()
{
    FragColor = vec4(1.0);
}