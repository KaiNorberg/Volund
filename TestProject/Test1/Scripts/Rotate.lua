local Rotate = {}

local TotalTime = 0.0

function Rotate.OnUpdate(Entity, TS)
    TotalTime = TotalTime + TS
    X = math.abs(math.cos(TotalTime))
    Entity:GetComponent(Component.TRANSFORM):SetScale(Vec3:new(1.0 * X, 1.0 * X, 1.0 * X))
    Entity:GetComponent(Component.TRANSFORM):AddRotation(Vec3:new(0.0, 90.0 * TS, 0.0))
end

return Rotate