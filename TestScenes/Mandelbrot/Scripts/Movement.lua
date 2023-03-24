local Movement = {
    Iter = 1000,
    Position = Vec2:new(0.5, 0.0),
    Scale = 1.0,

    IterStepsize = 1000,
    PositionStepsize = 2.0,
    ScaleStepsize = 1.0,
    JuliaCStepsize = 0.25,

    Julia = false,
    JuliaC = 0.0
}

function Movement.Control(Value, Upkey, DownKey, StepSize, TimeStep)
    if Input:IsHeld(Upkey) then
        return Value + StepSize * TimeStep 
    elseif Input:IsHeld(DownKey) then
        return Value - StepSize * TimeStep 
    else
        return Value
    end    
end

function Movement:OnUpdate(TimeStep)    
    EntityMat = self.Entity:Get(Component.MESH_RENDERER):GetMaterial()

    EntityMat:SetInt("Julia", self.Julia)   
    EntityMat:SetDouble("JuliaC", self.JuliaC)

    EntityMat:SetInt("MaxIterations", self.Iter)
    EntityMat:SetVec2("Position", self.Position)
    EntityMat:SetDouble("Scale", self.Scale)

    if Input:IsPressed('J') then
        if self.Julia == 1 then
            self.Julia = 0
        else
            self.Julia = 1
        end
    end

    self.Iter = self.Control(self.Iter, 'E', 'Q', self.IterStepsize, TimeStep)
    self.JuliaC = self.Control(self.JuliaC, 'T', 'G', self.JuliaCStepsize, TimeStep)
    self.Position.y = self.Control(self.Position.y, 'S', 'W', self.PositionStepsize * self.Scale, TimeStep)
    self.Position.x = self.Control(self.Position.x, 'A', 'D', self.PositionStepsize * self.Scale, TimeStep)
    self.Scale = self.Control(self.Scale, 'R', 'F', self.ScaleStepsize * self.Scale, TimeStep)
end

return Movement