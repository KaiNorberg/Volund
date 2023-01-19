Rotate = require("Scripts/Rotate.lua")

BlipSound = Sound:new("Sound/Blip.wav")

SimpleShader = Shader:new("Simple.vshader")

SphereMesh = Mesh:new("Sphere.vobj")

RedMaterial = Material:new(SimpleShader)
RedMaterial:SetVec3("Color", Vec3:new(1.0, 0.0, 0.0))

BlueMaterial = Material:new(SimpleShader)
BlueMaterial:SetVec3("Color", Vec3:new(0.0, 0.0, 1.0))

Camera = Scene:CreateEntity()
Camera:AddComponent(Component.TRANSFORM, {Position = Vec3:new(0.0, 0.0, 0.0)})
Camera:AddComponent(Component.CAMERA, {IsActive = true})
Camera:AddComponent(Component.CAMERA_MOVEMENT, {Sensitivity = 0.5, Speed = 8})

PointLight = Scene:CreateEntity()
PointLight:AddComponent(Component.TRANSFORM, {Position = Vec3:new(0.0, 0.0, 0.0)})
PointLight:AddComponent(Component.POINT_LIGHT, {Brightness = 1.0, Color = Vec3:new(1.0, 1.0, 1.0)})

Sphere1 = Scene:CreateEntity()
Sphere1:AddComponent(Component.TRANSFORM, {Position = Vec3:new(0.0, 10.0, 0.0)})
Sphere1:AddComponent(Component.MESH_RENDERER, {Mesh = SphereMesh, Material = RedMaterial})
Sphere1:AddComponent(Component.SOUND_SOURCE, {Sound = BlipSound})
Sphere1:AddComponent(Component.SCRIPT, {Script = Rotate, SinDir = Vec3:new(10.0, 0.0, 0.0), CosDir = Vec3:new(0.0, 10.0, 0.0)})

Sphere2 = Scene:CreateEntity()
Sphere2:AddComponent(Component.TRANSFORM, {Position = Vec3:new(0.0, 0.0, 10.0)})
Sphere2:AddComponent(Component.MESH_RENDERER, {Mesh = SphereMesh, Material = BlueMaterial})
Sphere2:AddComponent(Component.SCRIPT, {Script = Rotate, SinDir = Vec3:new(-10.0, 0.0, 0.0), CosDir = Vec3:new(0.0, 0.0, 10.0)})

Window:SetCursorMode(CursorMode.DISABLED)