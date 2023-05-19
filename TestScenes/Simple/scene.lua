local table =
{
	{
		{
			state.Enums.Component.Transform,
			Position = Vec3:new(0.000000, 2.000000, 10.000000),
			Rotation = Vec3:new(0.000000, -0.000000, 0.000000),
			Scale = Vec3:new(1.000000, 1.000000, 1.000000)
		},
		{
			state.Enums.Component.Camera,
			FOV = 80.000000,
			NearPlane = 0.100000,
			FarPlane = 100.000000
		},
		{
			state.Enums.Component.Tag,
			String = "Camera"
		}
	},
	{
		{
			state.Enums.Component.Transform,
			Position = Vec3:new(0.000000, 7.500000, 0.000000),
			Rotation = Vec3:new(0.000000, -0.000000, 0.000000),
			Scale = Vec3:new(1.000000, 1.000000, 1.000000)
		},
		{
			state.Enums.Component.PointLight,
			Color = Vec3:new(1.000000, 1.000000, 1.000000),
			Brightness = 1.000000
		},
		{
			state.Enums.Component.Tag,
			String = "Light"
		}
	},
	{
		{
			state.Enums.Component.Transform,
			Position = Vec3:new(-3.000000, 0.000000, 0.000000),
			Rotation = Vec3:new(0.000000, -0.000000, 0.000000),
			Scale = Vec3:new(1.000000, 1.000000, 1.000000)
		},
		{
			state.Enums.Component.MeshRenderer,
			Mesh = "://Cube.obj",
			Material = "Materials/Texture.mat.lua"
		},
		{
			state.Enums.Component.Tag,
			String = "TexturedCube"
		}
	},
	{
		{
			state.Enums.Component.Transform,
			Position = Vec3:new(-6.800000, 4.500000, -7.600000),
			Rotation = Vec3:new(0.000000, -0.000000, 0.000000),
			Scale = Vec3:new(1.000000, 1.000000, 1.000000)
		},
		{
			state.Enums.Component.MeshRenderer,
			Mesh = "://Cube.obj",
			Material = "Materials/Green.mat.lua"
		},
		{
			state.Enums.Component.Tag,
			String = "GreenCube"
		}
	},
	{
		{
			state.Enums.Component.Transform,
			Position = Vec3:new(0.000000, -10.000000, 0.000000),
			Rotation = Vec3:new(0.000000, -0.000000, 0.000000),
			Scale = Vec3:new(1000.000000, 1.000000, 1000.000000)
		},
		{
			state.Enums.Component.MeshRenderer,
			Mesh = "://Cube.obj",
			Material = "Materials/White.mat.lua"
		},
		{
			state.Enums.Component.Tag,
			String = "Ground"
		}
	},
	{
		{
			state.Enums.Component.Transform,
			Position = Vec3:new(3.000000, 0.000000, 0.000000),
			Rotation = Vec3:new(0.000000, -0.000000, 0.000000),
			Scale = Vec3:new(1.000000, 1.000000, 1.000000)
		},
		{
			state.Enums.Component.MeshRenderer,
			Mesh = "..\TestScenes\Simple\Models\Teapot.obj",
			Material = "..\TestScenes\Simple\Materials\Blue.mat.lua"
		},
		{
			state.Enums.Component.Tag,
			String = "BlueTeapot"
		}
	}
}

return table