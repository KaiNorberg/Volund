local Movement = {}

local Iter = 1000
local Position = Vec2:new(0.5, 0.0)
local Scale = 1.0

local IterStepsize = 1000
local PositionStepsize = 2.0
local ScaleStepsize = 1.0
local JuliaCStepsize = 0.25

local Julia = false
local JuliaC = 0.0

function Control(Value, Upkey, DownKey, StepSize, TimeStep)
    if Input:IsHeld(Upkey) then
        return Value + StepSize * TimeStep 
    elseif Input:IsHeld(DownKey) then
        return Value - StepSize * TimeStep 
    else
        return Value
    end    
end

function Movement.OnUpdate(Entity, TimeStep)
    
    EntityMat = Entity:GetComponent(Component.MESH_RENDERER):GetMaterial()

    EntityMat:SetInt("Julia", Julia)   
    EntityMat:SetDouble("JuliaC", JuliaC)

    EntityMat:SetInt("MaxIterations", Iter)
    EntityMat:SetVec2("Position", Position)
    EntityMat:SetDouble("Scale", Scale)

    if Input:IsPressed('J') then
        if Julia == 1 then
            Julia = 0
        else
            Julia = 1
        end
    end

    Iter = Control(Iter, 'E', 'Q', IterStepsize, TimeStep)
    JuliaC = Control(JuliaC, 'T', 'G', JuliaCStepsize, TimeStep)
    Position.y = Control(Position.y, 'S', 'W', PositionStepsize * Scale, TimeStep)
    Position.x = Control(Position.x, 'A', 'D', PositionStepsize * Scale, TimeStep)
    Scale = Control(Scale, 'R', 'F', ScaleStepsize * Scale, TimeStep)
end

return Movement