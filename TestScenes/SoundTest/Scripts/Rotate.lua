local Rotate = 
{
    TotalTime = 0.0
}

function Rotate:OnCreate(Args)
    self.SinDir = Args["SinDir"]
    self.CosDir = Args["CosDir"]
end

function Rotate:OnUpdate(TS)
    self.TotalTime = self.TotalTime + TS
    self.Entity:GetComponent(Component.TRANSFORM):SetPosition(self.SinDir * math.sin(self.TotalTime * math.pi) + self.CosDir * math.cos(self.TotalTime * math.pi))
end

return Rotate