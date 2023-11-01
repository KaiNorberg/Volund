local table =
{	
	FileType = "Material",
	Data = 
	{
		Shader = "Shaders/Mandelbrot.shader",
		Uniforms =
		{
			Julia = 0,
			MaxIterations = 1000,
			JuliaC = 0.500000,
			Scale = 0.200000,
			Position = Vec2:new(0.500000, 0.000000)
		}
	}
}

return table