PlayerMovement = require("Scripts/PlayerMovement.lua")
PortalScript = require("Scripts/PortalScript.lua")
HoverScript = require("Scripts/HoverScript.lua")

PBRShader = Shader:new("PBR.vshader")
PBRTextureShader = Shader:new("PBRTexture.vshader")
PortalShader = Shader:new("Shaders/Portal.vshader")

CubeMesh = Mesh:new("Cube.vobj")
SphereMesh = Mesh:new("Sphere.vobj")
ArchMesh = Mesh:new("Models/Arch.obj")
PillarMesh = Mesh:new("Models/Pillar.obj")

GroundMaterial = Material:new(PBRShader)
GroundMaterial:SetVec3("Albedo", Vec3:new(1.0, 1.0, 1.0))
GroundMaterial:SetFloat("Metalness", 0.2)
GroundMaterial:SetFloat("Roughness", 0.9)

SphereMaterial = Material:new(PBRShader)
SphereMaterial:SetVec3("Albedo", Vec3:new(1.0, 0.0, 0.0))
SphereMaterial:SetFloat("Metalness", 0.2)
SphereMaterial:SetFloat("Roughness", 0.9)

ArchMaterial = Material:new(PBRTextureShader)
ArchMaterial:SetTexture("AlbedoTexture", Texture:new("Textures/arch2_Albedo.png"))
ArchMaterial:SetTexture("MetalTexture", Texture:new("Textures/arch2_Roughness.png"))
ArchMaterial:SetTexture("RoughTexture", Texture:new("Textures/arch2_Roughness.png"))

PillarMaterial = Material:new(PBRTextureShader)
PillarMaterial:SetTexture("AlbedoTexture", Texture:new("Textures/column_01_DefaultMaterial_Diffuse.jpg"))
PillarMaterial:SetTexture("MetalTexture", Texture:new("Textures/column_01_DefaultMaterial_Specular.jpg"))
PillarMaterial:SetTexture("RoughTexture", Texture:new("Textures/column_01_DefaultMaterial_Glossiness.jpg"))

Pillar = Scene:CreateEntity();
Pillar:AddComponent(Component.TRANSFORM, {Position = Vec3:new(10, 0.0, -10.0)})
Pillar:AddComponent(Component.MESH_RENDERER, {Mesh = PillarMesh, Material = PillarMaterial})

Ground = Scene:CreateEntity();
Ground:AddComponent(Component.TRANSFORM, {Position = Vec3:new(0.0, 0.0, 0.0), Scale = Vec3:new(1000.0, 1.0, 1000.0)})
Ground:AddComponent(Component.MESH_RENDERER, {Mesh = CubeMesh, Material = GroundMaterial})

Sphere = Scene:CreateEntity();
Sphere:AddComponent(Component.TRANSFORM, {Position = Vec3:new(-10.0, 0.0, -10.0), Scale = Vec3:new(1.0, 1.0, 1.0)})
Sphere:AddComponent(Component.MESH_RENDERER, {Mesh = SphereMesh, Material = SphereMaterial})
Sphere:AddComponent(Component.SCRIPT, {Script = HoverScript})

Camera = Scene:CreateEntity()
Camera:AddComponent(Component.TRANSFORM, {Position = Vec3:new(0.0, 2.0, 10.0)})
Camera:AddComponent(Component.CAMERA, {FOV = 80})
Camera:AddComponent(Component.CAMERA_MOVEMENT, {Sensitivity = 0.5, Speed = 8})
Camera:AddComponent(Component.SCRIPT, {Script = PlayerMovement, Ground = Ground})

PointLight = Scene:CreateEntity()
PointLight:AddComponent(Component.TRANSFORM, {Position = Vec3:new(3.0, 7.5, 3.0) * 50.0})
PointLight:AddComponent(Component.POINT_LIGHT, {Brightness = 500000.0, Color = Vec3:new(1.0, 1.0, 1.0)})

Window:SetCursorMode(CursorMode.DISABLED)

function CreatePortal(Position)
    Arch = Scene:CreateEntity();
    Arch:AddComponent(Component.TRANSFORM, {Position = Position, Rotation = Vec3:new(0.0, 180.0, 0.0)})
    Arch:AddComponent(Component.MESH_RENDERER, {Mesh = ArchMesh, Material = ArchMaterial, Layer = 2})
    
    Portal = Scene:CreateEntity();
    Portal:AddComponent(Component.TRANSFORM, {Position = Position + Vec3:new(0.0, 2.0, -0.2), Scale = Vec3:new(4.5, 7.0, 0.7)})
    Portal:AddComponent(Component.MESH_RENDERER, {Mesh = CubeMesh, Material = Material:new(PortalShader), Layer = 2})
    return Portal
end

function ConnectPortals(Portal1, Portal2)
    Portal1:AddComponent(Component.SCRIPT, {Script = PortalScript, TargetPortal = Portal2, Player = Camera})
    Portal2:AddComponent(Component.SCRIPT, {Script = PortalScript, TargetPortal = Portal1, Player = Camera})
end

ConnectPortals(CreatePortal(Vec3:new(-10.0, 0.0, 0.0)), CreatePortal(Vec3:new(10.0, 0.0, 0.0)))
