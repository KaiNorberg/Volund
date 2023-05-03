local scene =
{
    {
        {
            state.Enums.Component.Transform,
            Position = Vec3:new(0.0, 2.0, 10.0)
        },
        {
            state.Enums.Component.Camera
        },
        --{Component.CameraMovement, Sensitivity = 0.5, Speed = 8}
    },
    {
        {
            state.Enums.Component.Transform,
            Position = Vec3:new(0.0, 7.5, 0.0)
        },
        {
            state.Enums.Component.PointLight,
            Brightness = 1.0,
            Color = Vec3:new(1.0, 1.0, 1.0)
        }
    },
    {
        {
            state.Enums.Component.Transform,
            Position = Vec3:new(-3.0, 0.0, 0.0)
        },
        {
            state.Enums.Component.MeshRenderer,
            Mesh = "://Cube.obj",
            Material = "Materials/Texture.mat.lua"
        },
        --{Component.Script, Script = Rotate}
    },
    {
        {
            state.Enums.Component.Transform,
            Position = Vec3:new(-6.8, 4.5, -7.6)
        },
        {
            state.Enums.Component.MeshRenderer,
            Mesh = "://Cube.obj",
            Material = "Materials/Green.mat.lua"
        }
    },
    {
        {
            state.Enums.Component.Transform,
            Position = Vec3:new(2.9, 0.0, 0.0)
        },
        {
            state.Enums.Component.MeshRenderer,
            Mesh = "Models/Teapot.obj",
            Material = "Materials/Blue.mat.lua"
        }
    },
    {
        {
            state.Enums.Component.Transform,
            Position = Vec3:new(0.0, -10.0, 0.0),
            Scale = Vec3:new(1000, 1, 1000)
        },
        {
            state.Enums.Component.MeshRenderer,
            Mesh = "://Cube.obj",
            Material = "Materials/White.mat.lua"
        }
    }
}

return scene