Scale = require("Scripts/Scale.lua")

SimpleShader = Shader:new("Simple.vshader")

RedMaterial = Material:new(SimpleShader)
RedMaterial:SetVec3("Color", Vec3:new(1.0, 0.0, 0.0))
RedMaterial:SetFloat("AmbientLighting", 1.0)

BlueMaterial = Material:new(SimpleShader)
BlueMaterial:SetVec3("Color", Vec3:new(0.0, 0.0, 1.0))
BlueMaterial:SetFloat("AmbientLighting", 1.0)

CubeMesh = Mesh:new("Cube.vobj")

function ShowFPS(Entity, TS)
    --Print(1.0 / TS)
end
Camera = Scene:CreateEntity()
Camera:AddComponent(Component.TRANSFORM, {Position = Vec3:new(0.0, 0.0, 25.0)})
Camera:AddComponent(Component.CAMERA, {IsActive = true})
Camera:AddComponent(Component.SCRIPT, {OnUpdate = ShowFPS})

Count = 20

for X = -Count / 2, Count / 2 do
    for Y = -Count / 2, Count / 2 do
        for Z = -Count / 2, Count / 2 do
            NewEntity = Scene:CreateEntity()

            NewEntity:AddComponent(Component.TRANSFORM, {Position = Vec3:new(X, Y, Z), Scale})
            NewEntity:AddComponent(Component.SCRIPT, {OnUpdate = Scale.OnUpdate})
            
            if math.abs(Z) % 2 == 0 then
                NewEntity:AddComponent(Component.MESH_RENDERER, {Mesh = CubeMesh, Material = BlueMaterial})
            else
                NewEntity:AddComponent(Component.MESH_RENDERER, {Mesh = CubeMesh, Material = RedMaterial})
            end
        end
    end
end

Window:SetCursorMode(CursorMode.DISABLED)