Movement = require("Scripts/Movement.lua")

MandelbrotShader = Shader:new("Shaders/Mandelbrot.shader")
MandelbrotMaterial = Material:new(MandelbrotShader)
QuadMesh = Mesh:new("Quad.vobj")

Camera = Scene:CreateEntity()
Camera:AddComponent(Component.TRANSFORM, {Position = Vec3:new(0.0, 0.0, 0.1)})
Camera:AddComponent(Component.CAMERA, {IsActive = true})

Mandelbrot = Scene:CreateEntity()
Mandelbrot:AddComponent(Component.MESH_RENDERER, {Mesh = QuadMesh, Material = MandelbrotMaterial})
Mandelbrot:AddComponent(Component.SCRIPT, {Script = Movement})