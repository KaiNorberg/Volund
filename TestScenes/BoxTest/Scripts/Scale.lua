local Scale = {}

function Scale:OnUpdate(TimeStep)
    X = math.abs(math.cos(Scene:TimeSinceStart()))
    self.Entity:GetComponent(Component.TRANSFORM):SetScale(Vec3:new(X))
end

return Scale