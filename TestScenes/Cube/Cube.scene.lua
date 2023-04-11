local scene =
{
    {
        {Component.Transform, Position = Vec3:new(0.0, 0.0, 4.0)},
        {Component.Camera}
    },
    {
        {Component.Transform, Position = Vec3:new(0.0, 5.0, 5.0)},
        {Component.PointLight, Brightness = 1.0, Color = Vec3:new(1.0, 1.0, 1.0)}
    },
    {
        {Component.Transform, Position = Vec3:new(2.0, 0.0, 0.0)},
        {Component.MeshRenderer, Mesh = "://Cube.obj", Material = "Materials/Red.mat.lua"}
    },
    {
        {Component.Transform, Position = Vec3:new(-2.0, 0.0, 0.0)},
        {Component.MeshRenderer, Mesh = "://Cube.obj", Material = "Materials/Red.mat.lua"}
    }
}

return scene