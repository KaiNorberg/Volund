Movement = require("Scripts/Movement.lua")
ShowFPS = require("../Common/ShowFPS.lua")

MandelbrotShader = Shader:new("Shaders/Mandelbrot.shader")
MandelbrotMaterial = Material:new(MandelbrotShader)
QuadMesh = Mesh:new("Quad.vobj")

Camera = Scene:CreateEntity()
Camera:Add(Component.TRANSFORM, {Position = Vec3:new(0.0, 0.0, 0.1)})
Camera:Add(Component.CAMERA, {IsActive = true, NearPlane = 0.000000001})
Camera:Add(Component.SCRIPT, {Script = ShowFPS})

Mandelbrot = Scene:CreateEntity()
Mandelbrot:Add(Component.MESH_RENDERER, {Mesh = QuadMesh, Material = MandelbrotMaterial})
Mandelbrot:Add(Component.SCRIPT, {Script = Movement})