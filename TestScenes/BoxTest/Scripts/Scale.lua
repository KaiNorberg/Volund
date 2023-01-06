local Scale = 
{
    Scale = Vec3:new(0.0)
}

function Scale:OnCreate(TimeStep)
    self.Transform = self.Entity:GetComponent(Component.TRANSFORM)
end

function Scale:OnUpdate(TimeStep)
    X = math.abs(math.cos(Scene:TimeSinceStart()))
    self.Scale.x = X
    self.Scale.y = X
    self.Scale.z = X
    self.Transform:SetScale(self.Scale)
end

return Scale