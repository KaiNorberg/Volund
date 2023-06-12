local HoverScript = 
{

}

function HoverScript:OnCreate(Args)
    
end

function HoverScript:OnUpdate(TS)
    Position = self.Entity:Get(Component.TRANSFORM):GetPosition()
    Position.y = 3 + math.sin(Scene:TimeSinceStart() * 2) / 3
    self.Entity:Get(Component.TRANSFORM):SetPosition(Position)
end

return HoverScript