local Scale = {}

local TotalTime = 0.0

function Scale.OnUpdate(Entity, TS)
    TotalTime = TotalTime + TS / 2 ^ 13
    X = math.abs(math.cos(TotalTime))
    Entity:GetComponent(Component.TRANSFORM):SetScale(Vec3:new(X))
end

return Scale