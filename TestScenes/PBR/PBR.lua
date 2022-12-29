PBRShader = Shader:new("PBR.vshader")

SphereMesh = Mesh:new("Sphere.vobj")

Camera = Scene:CreateEntity()
Camera:AddComponent(Component.TRANSFORM, {Position = Vec3:new(0.0, 0.0, 20.0)})
Camera:AddComponent(Component.CAMERA, {IsActive = true})
Camera:AddComponent(Component.CAMERA_MOVEMENT, {Sensitivity = 0.5, Speed = 8})

PointLight = Scene:CreateEntity()
PointLight:AddComponent(Component.TRANSFORM, {Position = Vec3:new(0.0, 0, 150.0)})
PointLight:AddComponent(Component.POINT_LIGHT, {Brightness = 100000.0, Color = Vec3:new(1.0, 0.0, 0.0)})

for x = 0,10 do
    for y = 0,10 do
        local NewMaterial = Material:new(PBRShader)
        NewMaterial:SetVec3("Albedo", Vec3:new(1.0, 1.0, 1.0))
        NewMaterial:SetFloat("Metalness", math.min(x * 0.1, 1.0))
        NewMaterial:SetFloat("Roughness", math.min(y * 0.1, 1.0))
        
        local NewEntity = Scene:CreateEntity()
        NewEntity:AddComponent(Component.TRANSFORM, {Position = Vec3:new((x - 5) * 2.5, (y - 5) * 2.5, 0.0)})
        NewEntity:AddComponent(Component.MESH_RENDERER, {Mesh = SphereMesh, Material = NewMaterial})
    end
end

Window:SetCursorMode(CursorMode.DISABLED)