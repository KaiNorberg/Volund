Rotate = require("Scripts/Rotate.lua")

SimpleShader = Shader:new("Simple.vshader")
SimpleTextureShader = Shader:new("SimpleTexture.vshader")

TestTexture = Texture:new("Textures/Test.jpg")

CubeMesh = Mesh:new("Cube.vobj")
TeapotMesh = Mesh:new("Models/Teapot.obj")

TextureMaterial = Material:new(SimpleTextureShader)
TextureMaterial:SetTexture("ColorTexture", TestTexture)

GreenMaterial = Material:new(SimpleShader)
GreenMaterial:SetVec3("Color", Vec3:new(0.0, 1.0, 0.0))

BlueMaterial = Material:new(SimpleShader)
BlueMaterial:SetVec3("Color", Vec3:new(0.0, 0.0, 1.0))

WhiteMaterial = Material:new(SimpleShader)
WhiteMaterial:SetVec3("Color", Vec3:new(1.0, 1.0, 1.0))

Camera = Scene:CreateEntity()
Camera:AddComponent(Component.TRANSFORM, {Position = Vec3:new(0.0, 2.0, 10.0)})
Camera:AddComponent(Component.CAMERA, {IsActive = true})
Camera:AddComponent(Component.CAMERA_MOVEMENT, {Sensitivity = 0.5, Speed = 8})

TextureCube = Scene:CreateEntity()
TextureCube:AddComponent(Component.TRANSFORM, {Position = Vec3:new(-3.0, 0.0, 0.0)})
TextureCube:AddComponent(Component.MESH_RENDERER, {Mesh = CubeMesh, Material = TextureMaterial})
TextureCube:AddComponent(Component.SCRIPT, {Script = Rotate})

GreenCube = Scene:CreateEntity()
GreenCube:AddComponent(Component.TRANSFORM, {Position = Vec3:new(-6.8, 4.5, -7.6)})
GreenCube:AddComponent(Component.MESH_RENDERER, {Mesh = CubeMesh, Material = GreenMaterial})

PointLight = Scene:CreateEntity()
PointLight:AddComponent(Component.TRANSFORM, {Position = Vec3:new(0.0, 7.5, 0.0)})
PointLight:AddComponent(Component.POINT_LIGHT, {Brightness = 1.0, Color = Vec3:new(1.0, 1.0, 1.0)})

Teapot = Scene:CreateEntity()
Teapot:AddComponent(Component.TRANSFORM, {Position = Vec3:new(2.9, 0.0, 0.0)})
Teapot:AddComponent(Component.MESH_RENDERER, {Mesh = TeapotMesh, Material = BlueMaterial})

Ground = Scene:CreateEntity()
Ground:AddComponent(Component.TRANSFORM, {Position = Vec3:new(0.0, -10.0, 0.0), Scale = Vec3:new(1000, 1, 1000)})
Ground:AddComponent(Component.MESH_RENDERER, {Mesh = CubeMesh, Material = WhiteMaterial})

Window:SetCursorMode(CursorMode.DISABLED)