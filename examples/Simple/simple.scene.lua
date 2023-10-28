local table =
{
	FileType = "Scene",
	Data = 
	{
		{
			{
				ComponentType = 6,
				String = "Camera"
			},
			{
				ComponentType = 7,
				Position = Vec3:new(0.000000, 2.000000, 8.000000),
				Rotation = Vec3:new(0.000000, -0.000000, 0.000000),
				Scale = Vec3:new(1.000000, 1.000000, 1.000000)
			},
			{
				ComponentType = 1,
				FOV = 80.000000,
				NearPlane = 0.100000,
				FarPlane = 100.000000
			}
		},
		{
			{
				ComponentType = 6,
				String = "Light"
			},
			{
				ComponentType = 7,
				Position = Vec3:new(0.000000, 7.500000, 0.000000),
				Rotation = Vec3:new(0.000000, -0.000000, 0.000000),
				Scale = Vec3:new(1.000000, 1.000000, 1.000000)
			},
			{
				ComponentType = 4,
				Color = Vec3:new(1.000000, 1.000000, 1.000000),
				Brightness = 500.000000
			}
		},
		{
			{
				ComponentType = 6,
				String = "TexturedCube"
			},
			{
				ComponentType = 7,
				Position = Vec3:new(-5.000000, 0.000000, 0.000000),
				Rotation = Vec3:new(0.000000, -0.000000, 0.000000),
				Scale = Vec3:new(1.000000, 1.000000, 1.000000)
			},
			{
				ComponentType = 3,
				Mesh = "://Cube.obj",
				Material = "Materials/Texture.material.lua"
			}
		},
		{
			{
				ComponentType = 6,
				String = "GreenCube"
			},
			{
				ComponentType = 7,
				Position = Vec3:new(-6.800000, 4.500000, -7.600000),
				Rotation = Vec3:new(0.000000, -0.000000, 0.000000),
				Scale = Vec3:new(1.000000, 1.000000, 1.000000)
			},
			{
				ComponentType = 3,
				Mesh = "://Cube.obj",
				Material = "Materials/Green.mat.lua"
			},
			{
				ComponentType = 10,
				Filepath = "Scripts/Rotate.lua",
				PublicVars =
				{

				}
			}
		},
		{
			{
				ComponentType = 6,
				String = "Teapot"
			},
			{
				ComponentType = 7,
				Position = Vec3:new(5.000000, 0.000000, 0.000000),
				Rotation = Vec3:new(0.000000, -0.000000, 0.000000),
				Scale = Vec3:new(1.000000, 1.000000, 1.000000)
			},
			{
				ComponentType = 3,
				Mesh = "Models/Teapot.obj",
				Material = "Materials/White.mat.lua"
			}
		},
		{
			{
				ComponentType = 6,
				String = "BlueCube"
			},
			{
				ComponentType = 7,
				Position = Vec3:new(7.500000, 3.000000, -7.800000),
				Rotation = Vec3:new(0.000000, -0.000000, 0.000000),
				Scale = Vec3:new(1.000000, 1.000000, 1.000000)
			},
			{
				ComponentType = 3,
				Mesh = "://Cube.obj",
				Material = "Materials/Blue.mat.lua"
			}
		}
	}
}

return table