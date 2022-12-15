SimpleShader = Shader:new("Simple.vshader")

RedMaterial = Material:new(SimpleShader)
RedMaterial:SetVec3("Color", Vec3:new(1.0, 0.0, 0.0))
RedMaterial:SetFloat("AmbientLighting", 1.0)

BlueMaterial = Material:new(SimpleShader)
BlueMaterial:SetVec3("Color", Vec3:new(0.0, 0.0, 1.0))
BlueMaterial:SetFloat("AmbientLighting", 1.0)

CubeMesh = Mesh:new("Cube.vobj")

function ShowFPS(Entity, TS)
    Print(1.0 / TS)
end

Camera = Entity:new()
Camera:AddComponent(Component.TRANSFORM, {Position = Vec3:new(0.0, 0.0, 10.0)})
Camera:AddComponent(Component.CAMERA, {IsActive = true})
Camera:AddComponent(Component.CAMERA_MOVEMENT, {Speed = 15, Senitivity = 0.5})
Camera:AddComponent(Component.SCRIPT, {OnUpdate = ShowFPS})

for i = 0, 10000 do
    NewEntity = Entity:new()

    NewEntity:AddComponent(Component.TRANSFORM, {Position = Vec3:new(math.random(-10, 10), math.random(-10, 10), math.random(-10, 10))})
    
    if i % 2 == 0 then
        NewEntity:AddComponent(Component.MESH_RENDERER, {Mesh = CubeMesh, Material = RedMaterial})
    else
        NewEntity:AddComponent(Component.MESH_RENDERER, {Mesh = CubeMesh, Material = BlueMaterial})
    end
end

Window:SetCursorMode(CursorMode.DISABLED)