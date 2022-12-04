Rotate = VolundRequire("Scripts/Rotate.lua")

RedMaterial = Material:new("Simple.vshader")
RedMaterial:SetVec3("Color", Vec3:new(1.0, 0.0, 0.0))

GreenMaterial = Material:new("Simple.vshader")
GreenMaterial:SetVec3("Color", Vec3:new(0.0, 1.0, 0.0))

BlueMaterial = Material:new("Simple.vshader")
BlueMaterial:SetVec3("Color", Vec3:new(0.0, 0.0, 1.0))

CubeMesh = Mesh:new("Cube.obj")
TeapotMesh = Mesh:new("Models/Teapot.obj")

Camera = Entity:new()

Camera:AddComponent(Component.TRANSFORM, {Position = Vec3:new(0.0, 2.0, 10.0)})
Camera:AddComponent(Component.CAMERA, {IsActive = true})
Camera:AddComponent(Component.CAMERA_MOVEMENT, {Sensitivity = 0, Speed = 8})

RedCube = Entity:new()

RedCube:AddComponent(Component.TRANSFORM, {Position = Vec3:new(-3.0, 0.0, 0.0)})
RedCube:AddComponent(Component.MESH_RENDERER, {Mesh = CubeMesh, Material = RedMaterial})

GreenCube = Entity:new()

GreenCube:AddComponent(Component.TRANSFORM, {Position = Vec3:new(-6.8, 4.5, -7.6)})
GreenCube:AddComponent(Component.MESH_RENDERER, {Mesh = CubeMesh, Material = GreenMaterial})
GreenCube:AddComponent(Component.SCRIPT, {OnUpdate = Rotate.OnUpdate})

PointLight = Entity:new()

PointLight:AddComponent(Component.TRANSFORM, {Position = Vec3:new(0.0, 7.5, 0.0)})
PointLight:AddComponent(Component.POINT_LIGHT, {Brightness = 1.0, Color = Vec3:new(1.0, 1.0, 1.0)})

Teapot = Entity:new()

Teapot:AddComponent(Component.TRANSFORM, {Position = Vec3:new(2.9, 0.0, 0.0)})
Teapot:AddComponent(Component.MESH_RENDERER, {Mesh = TeapotMesh, Material = BlueMaterial})