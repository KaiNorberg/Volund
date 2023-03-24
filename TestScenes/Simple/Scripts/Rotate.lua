local Rotate = 
{
    TotalTime = 0.0
}

function Rotate:OnUpdate(TS)
    self.TotalTime = self.TotalTime + TS
    X = math.abs(math.cos(self.TotalTime))
    self.Entity:Get(Component.TRANSFORM):SetScale(Vec3:new(1.0 * X, 1.0 * X, 1.0 * X))
    self.Entity:Get(Component.TRANSFORM):AddRotation(Vec3:new(0.0, 90.0 * TS, 0.0))
end

return Rotate