--Rotate = require("Scripts/Rotate.lua")

--Window:SetCursorMode(CursorMode.DISABLED)

local scene =
{
    {
        {Component.Transform, Position = Vec3:new(0.0, 2.0, 10.0)},
        {Component.Camera},
        {Component.CameraMovement, Sensitivity = 0.5, Speed = 8}
    },
    {
        {Component.Transform, Position = Vec3:new(0.0, 7.5, 0.0)},
        {Component.PointLight, Brightness = 1.0, Color = Vec3:new(1.0, 1.0, 1.0)}
    },
    {
        {Component.Transform, Position = Vec3:new(-3.0, 0.0, 0.0)},
        {Component.MeshRenderer, Mesh = "://Cube.obj", Material = "Materials/Texture.mat.lua"},
        --{Component.Script, Script = Rotate}
    },
    {
        {Component.Transform, Position = Vec3:new(-6.8, 4.5, -7.6)},
        {Component.MeshRenderer, Mesh = "://Cube.obj", Material = "Materials/Green.mat.lua"}
    },
    {
        {Component.Transform, Position = Vec3:new(2.9, 0.0, 0.0)},
        {Component.MeshRenderer, Mesh = "Models/Teapot.obj", Material = "Materials/Blue.mat.lua"}
    },
    {
        {Component.Transform, Position = Vec3:new(0.0, -10.0, 0.0), Scale = Vec3:new(1000, 1, 1000)},
        {Component.MeshRenderer, Mesh = "://Cube.obj", Material = "Materials/White.mat.lua"}
    }
}

return scene