ShowFPS = require("../Common/ShowFPS.lua")
Gravity = require("Scripts/Gravity.lua")
Controller = require("Scripts/Controller.lua")

--Variables

SystemRadius = 9 * 10^3
PlanetAmount = 15
PlanetScale = 0.3
StarScale = 0.002

MaxPlanetMass = 50
MinPlanetMass = 5
StarMass = 60000

--Setup

SimpleShader = Shader:new("Simple.vshader")

StarMaterial = Material:new(SimpleShader)
StarMaterial:SetVec3("Color", Vec3:new(1.0, 0.5, 0.0))
StarMaterial:SetVec3("AmbientLighting", Vec3:new(1.0))

SphereMesh = Mesh:new("Sphere.vobj")

Camera = Scene:CreateEntity()
Camera:AddComponent(Component.TRANSFORM, {Position = Vec3:new(0.0, SystemRadius, SystemRadius * 2)})
Camera:AddComponent(Component.CAMERA, {FarPlane = SystemRadius * 10^5})
Camera:AddComponent(Component.SCRIPT, {Script = ShowFPS})
Camera:AddComponent(Component.CAMERA_MOVEMENT, {Sensitivity = 0.5, Speed = SystemRadius})

--Create Galaxy

Star = Scene:CreateEntity()
Star:AddComponent(Component.TRANSFORM, {Position = Vec3:new(0.0), Scale = Vec3:new(((6 * StarMass) * math.pi) ^ 1/3 * StarScale)})
Star:AddComponent(Component.SCRIPT, {Script = Gravity, Mass = StarMass})
Star:AddComponent(Component.MESH_RENDERER, {Mesh = SphereMesh, Material = StarMaterial})

for i = 1, PlanetAmount do
    NewEntity = Scene:CreateEntity()

    R = SystemRadius * math.sqrt(math.random())
    Theta = math.random() * 2 * math.pi

    X = R * math.cos(Theta)
    Z = R * math.sin(Theta)
    Y = math.random(-SystemRadius / 20, SystemRadius / 20)

    PlanetMass = MinPlanetMass + math.random() * (MaxPlanetMass - MinPlanetMass)
    PlanetDiameter = ((6 * PlanetMass) * math.pi) ^ 1/3

    NewMaterial = Material:new(SimpleShader)
    NewMaterial:SetVec3("Color", Vec3:new(X, Y, Z))
    NewMaterial:SetVec3("AmbientLighting", Vec3:new(1.0))
    
    NewEntity:AddComponent(Component.TRANSFORM, {Position = Vec3:new(X, Y, Z), Scale = Vec3:new(PlanetScale * PlanetDiameter)})
    NewEntity:AddComponent(Component.SCRIPT, {Script = Gravity, Mass = PlanetMass})
    NewEntity:AddComponent(Component.MESH_RENDERER, {Mesh = SphereMesh, Material = NewMaterial})
end

Window:SetCursorMode(CursorMode.DISABLED)

Camera:AddComponent(Component.SCRIPT, {Script = Controller})