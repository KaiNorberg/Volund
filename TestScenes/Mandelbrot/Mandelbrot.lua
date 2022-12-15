Movement = require("Movement.lua")

MandelbrotShader = Shader:new("Mandelbrot.vshader")
MandelbrotMaterial = Material:new(MandelbrotShader)
QuadMesh = Mesh:new("Quad.vobj")

Camera = Entity:new()
Camera:AddComponent(Component.TRANSFORM, {Position = Vec3:new(0.0, 0.0, 0.1)})
Camera:AddComponent(Component.CAMERA, {IsActive = true})

Mandelbrot = Entity:new()
Mandelbrot:AddComponent(Component.MESH_RENDERER, {Mesh = QuadMesh, Material = MandelbrotMaterial})
Mandelbrot:AddComponent(Component.SCRIPT, {OnUpdate = Movement.OnUpdate})