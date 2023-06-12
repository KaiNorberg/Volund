local PlayerMovement = 
{
    
}

function PlayerMovement:OnCreate(Args)
    self.Ground = Args["Ground"]
end

function PlayerMovement:OnUpdate(TS)
    GroundHeight = self.Ground:Get(Component.TRANSFORM):GetPosition().y
    Transform = self.Entity:Get(Component.TRANSFORM)
    Position = Transform:GetPosition();
    Transform:SetPosition(Vec3:new(Position.x, GroundHeight + 2, Position.z))
end

return PlayerMovement