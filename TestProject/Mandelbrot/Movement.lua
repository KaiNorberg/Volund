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

Movement.MandelbrotMaterial = Material:new("Mandelbrot.vshader")

function Movement.OnUpdate(Entity, Timestep)
    Movement.MandelbrotMaterial:SetInt("Julia", Julia)   
    Movement.MandelbrotMaterial:SetDouble("JuliaC", JuliaC)

    Movement.MandelbrotMaterial:SetInt("MaxIterations", Iter)
    Movement.MandelbrotMaterial:SetVec2("Position", Position)
    Movement.MandelbrotMaterial:SetDouble("Scale", Scale)

    if Input:IsPressed('J') then
        if Julia == 1 then
            Julia = 0
        else
            Julia = 1
        end
    end

    if Input:IsHeld('E') then
        Iter = Iter + IterStepsize * Timestep 
    elseif Input:IsHeld('Q') then
        Iter = Iter - IterStepsize * Timestep 
    end

    if Input:IsHeld('T') then
        JuliaC = JuliaC + JuliaCStepsize * Timestep 
    elseif Input:IsHeld('G') then
        JuliaC = JuliaC - JuliaCStepsize * Timestep 
    end

    if Input:IsHeld('W') then
        Position.y = Position.y - PositionStepsize * Timestep * Scale
    elseif Input:IsHeld('S') then
        Position.y = Position.y + PositionStepsize * Timestep * Scale
    end

    if Input:IsHeld('A') then
        Position.x = Position.x + PositionStepsize * Timestep * Scale
    elseif Input:IsHeld('D') then
        Position.x = Position.x - PositionStepsize * Timestep * Scale
    end

    if Input:IsHeld('R') then
        Scale = Scale + ScaleStepsize * Timestep * Scale
    elseif Input:IsHeld('F') then
        Scale = Scale - ScaleStepsize * Timestep * Scale
    end
end

return Movement