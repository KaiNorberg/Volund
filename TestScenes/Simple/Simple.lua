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

Camera = Scene:CreateEntity({
    {Component.TRANSFORM, {Position = Vec3:new(0.0, 2.0, 10.0)}},
    {Component.CAMERA, {IsActive = true}},
    {Component.CAMERA_MOVEMENT, {Sensitivity = 0.5, Speed = 8}}
})

TextureCube = Scene:CreateEntity({
    {Component.TRANSFORM, {Position = Vec3:new(-3.0, 0.0, 0.0)}},
    {Component.MESH_RENDERER, {Mesh = CubeMesh, Material = TextureMaterial}},
    {Component.SCRIPT, {Script = Rotate}}
})

GreenCube = Scene:CreateEntity({
    {Component.TRANSFORM, {Position = Vec3:new(-6.8, 4.5, -7.6)}},
    {Component.MESH_RENDERER, {Mesh = CubeMesh, Material = GreenMaterial}}
})

PointLight = Scene:CreateEntity({
    {Component.TRANSFORM, {Position = Vec3:new(0.0, 7.5, 0.0)}},
    {Component.POINT_LIGHT, {Brightness = 1.0, Color = Vec3:new(1.0, 1.0, 1.0)}}
})

Teapot = Scene:CreateEntity({
    {Component.TRANSFORM, {Position = Vec3:new(2.9, 0.0, 0.0)}},
    {Component.MESH_RENDERER, {Mesh = TeapotMesh, Material = BlueMaterial}}
})

Ground = Scene:CreateEntity({
    {Component.TRANSFORM, {Position = Vec3:new(0.0, -10.0, 0.0), Scale = Vec3:new(1000, 1, 1000)}},
    {Component.MESH_RENDERER, {Mesh = CubeMesh, Material = WhiteMaterial}}
})

Window:SetCursorMode(CursorMode.DISABLED)