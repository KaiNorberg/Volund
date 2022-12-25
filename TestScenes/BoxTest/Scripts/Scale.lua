local Scale = 
{
    TotalTime = 0.0;
}

function Scale:OnUpdate(TimeStep)
    self.TotalTime = self.TotalTime + TimeStep
    X = math.abs(math.cos(self.TotalTime))
    self.Entity:GetComponent(Component.TRANSFORM):SetScale(Vec3:new(X))
end

return Scale