local table =
{
	{
		{
			ComponentType = 6,
			String = "Mandelbrot"
		},
		{
			ComponentType = 7,
			Position = Vec3:new(0.000000, 1.000000, 0.000000),
			Rotation = Vec3:new(0.000000, -0.000000, 0.000000),
			Scale = Vec3:new(1.000000, 1.000000, 1.000000)
		},
		{
			ComponentType = 3,
			Mesh = "://Quad.obj",
			Material = "Materials/Mandelbrot.mat.lua"
		}
	},
	{
		{
			ComponentType = 6,
			String = "Camera"
		},
		{
			ComponentType = 7,
			Position = Vec3:new(0.000000, 1.000000, 0.500000),
			Rotation = Vec3:new(0.000000, -0.000000, 0.000000),
			Scale = Vec3:new(1.000000, 1.000000, 1.000000)
		},
		{
			ComponentType = 1,
			FOV = 80.000000,
			NearPlane = 0.100000,
			FarPlane = 100.000000
		}
	}
}

return table