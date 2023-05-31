Rotate = require("Scripts/Rotate.lua")

BlipSound = Sound:new("Sound/Blip.wav")

SimpleShader = Shader:new("Simple.vshader")

SphereMesh = Mesh:new("Sphere.vobj")

RedMaterial = Material:new(SimpleShader)
RedMaterial:SetVec3("Color", Vec3:new(1.0, 0.0, 0.0))

BlueMaterial = Material:new(SimpleShader)
BlueMaterial:SetVec3("Color", Vec3:new(0.0, 0.0, 1.0))

Camera = Scene:CreateEntity()
Camera:Add(Component.TRANSFORM, {Position = Vec3:new(0.0, 0.0, 0.0)})
Camera:Add(Component.CAMERA, {IsActive = true})
Camera:Add(Component.SOUND_LISTENER)

PointLight = Scene:CreateEntity()
PointLight:Add(Component.TRANSFORM, {Position = Vec3:new(0.0, 0.0, 0.0)})
PointLight:Add(Component.POINT_LIGHT, {Brightness = 1.0, Color = Vec3:new(1.0, 1.0, 1.0)})

Sphere1 = Scene:CreateEntity()
Sphere1:Add(Component.TRANSFORM, {Position = Vec3:new(0.0, 0.0, 10.0)})
Sphere1:Add(Component.MESH_RENDERER, {Mesh = SphereMesh, Material = BlueMaterial})
Sphere1:Add(Component.SOUND_SOURCE, {Sound = BlipSound, Looping = true, Play = true, Gain = 2})
Sphere1:Add(Component.SCRIPT, {Script = Rotate, SinDir = Vec3:new(-10.0, 0.0, 0.0), CosDir = Vec3:new(0.0, 0.0, 10.0)})

Window:SetCursorMode(CursorMode.DISABLED)