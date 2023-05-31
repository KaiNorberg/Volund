local Gravity = 
{
    Mass = 0.0,
    Velocity = Vec3:new(0.0, 0.0, 0.0)
}

function Gravity:OnCreate(Args)
    self.Mass = Args["Mass"]
end

function Gravity:OnUpdate(TimeStep)

end

return Gravity