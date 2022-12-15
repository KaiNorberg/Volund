Rotate = require("Scripts/Rotate.lua")

SimpleShader = Shader:new("Simple.vshader")

TestTexture = Texture:new("Textures/Test.jpg")

CubeMesh = Mesh:new("Cube.vobj")
TeapotMesh = Mesh:new("Models/Teapot.obj")

TextureMaterial = Material:new(SimpleShader)
TextureMaterial:SetFloat("ColorTextureMix", 1.0)
TextureMaterial:SetTexture("ColorTexture", TestTexture)

GreenMaterial = Material:new(SimpleShader)
GreenMaterial:SetFloat("ColorTextureMix", 0.0)
GreenMaterial:SetVec3("Color", Vec3:new(0.0, 1.0, 0.0))

BlueMaterial = Material:new(SimpleShader)
BlueMaterial:SetFloat("ColorTextureMix", 0.0)
BlueMaterial:SetVec3("Color", Vec3:new(0.0, 0.0, 1.0))

Camera = Entity:new()
Camera:AddComponent(Component.TRANSFORM, {Position = Vec3:new(0.0, 2.0, 10.0)})
Camera:AddComponent(Component.CAMERA, {IsActive = true})
Camera:AddComponent(Component.CAMERA_MOVEMENT, {Sensitivity = 0.5, Speed = 8})

TextureCube = Entity:new()
TextureCube:AddComponent(Component.TRANSFORM, {Position = Vec3:new(-3.0, 0.0, 0.0)})
TextureCube:AddComponent(Component.MESH_RENDERER, {Mesh = CubeMesh, Material = TextureMaterial})
TextureCube:AddComponent(Component.SCRIPT, {OnUpdate = Rotate.OnUpdate})

GreenCube = Entity:new()
GreenCube:AddComponent(Component.TRANSFORM, {Position = Vec3:new(-6.8, 4.5, -7.6)})
GreenCube:AddComponent(Component.MESH_RENDERER, {Mesh = CubeMesh, Material = GreenMaterial})

PointLight = Entity:new()
PointLight:AddComponent(Component.TRANSFORM, {Position = Vec3:new(0.0, 7.5, 0.0)})
PointLight:AddComponent(Component.POINT_LIGHT, {Brightness = 1.0, Color = Vec3:new(1.0, 1.0, 1.0)})

Teapot = Entity:new()
Teapot:AddComponent(Component.TRANSFORM, {Position = Vec3:new(2.9, 0.0, 0.0)})
Teapot:AddComponent(Component.MESH_RENDERER, {Mesh = TeapotMesh, Material = BlueMaterial})

Window:SetCursorMode(CursorMode.DISABLED)