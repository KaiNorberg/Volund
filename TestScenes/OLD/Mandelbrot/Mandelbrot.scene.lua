--Movement = require("Scripts/Movement.lua")
--ShowFPS = require("../Common/ShowFPS.lua")

local scene =
{
    {
        {Component.Transform, Position = Vec3:new(0.0, 0.0, 0.1)},
        {Component.Camera},
        --{Component.Script, Script = ShowFPS}
    },
    {
        {Component.MeshRenderer, Mesh = "://Quad.obj", Material = "Materials/Mandelbrot.mat.lua"}
    }
}

return scene