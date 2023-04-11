local count = 2

local scene =
{
    {
        {Component.Transform, Position = Vec3:new(0.0, 0.0, 25)},
        {Component.Camera, NearPlane = 1.0}
        --{Component.Script, Script = ShowFPS}
    }
}
 
for x = -count / 2, count / 2 do
    for y = -count / 2, count / 2 do
        for z = -count / 2, count / 2 do
            local newEntity =
            {
                {Component.Transform, Position = Vec3:new(x, y, z)}
                --{Component.SCRIPT, Script = Scale}
            }

            if math.abs(z) % 2 == 0 then
                table.insert(newEntity, {Component.MeshRenderer, Mesh = "://Cube.obj", Material = "Materials/Blue.mat.lua"})
            else
                table.insert(newEntity, {Component.MeshRenderer, Mesh = "://Cube.obj", Material = "Materials/Red.mat.lua"})
            end

            table.insert(scene, newEntity)
        end
    end
end

return scene