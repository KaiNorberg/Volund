local Scale = {}

function Scale:OnCreate(TimeStep)
    self.Transform = self.Entity:GetComponent(Component.TRANSFORM)
end

function Scale:OnUpdate(TimeStep)
    X = math.abs(math.cos(Scene:TimeSinceStart()))
    self.Transform:SetScale(Vec3:new(X))
end

return Scale