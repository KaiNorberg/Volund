local table =
{
	{
		{
			ComponentType = 6,
			String = "Mandelbrot"
		},
		{
			ComponentType = 7,
			Position = Vec3:new(0.000000, 0.000000, 0.000000),
			Rotation = Vec3:new(0.000000, -0.000000, 0.000000),
			Scale = Vec3:new(1.000000, 1.000000, 1.000000)
		},
		{
			ComponentType = 3,
			Mesh = "://Quad.obj",
			Material = "Materials/Mandelbrot.mat.lua"
		}
	}
}

return table