Gravity = require("Scripts/Gravity.lua")

TimeUnit = 10^6 --Some number

BigG = 6.674 * 10^-11

local Controller = 
{

}

function Controller:OnCreate(Args)
    View = Scene:View(Gravity)
    StarMass = View[1].Mass
    for i = 2, #View do           
        Position = View[i].Entity:GetComponent(Component.TRANSFORM):GetPosition()

        Speed = math.sqrt((BigG * StarMass) / (Position:Length()))

        Direction = (Vec3:new(0.0) - Position):Normalize()

        View[i].Velocity = Direction:Cross(Vec3:new(0, 1, 0)):Normalize() * (Speed)
    end    
end

function Controller:OnUpdate(TimeStep)
    View = Scene:View(Gravity)
    for i = 1, #View do    

        Transform = View[i].Entity:GetComponent(Component.TRANSFORM)

        PositionOne = Transform:GetPosition()
        MassOne = View[i].Mass 

        for j = i + 1, #View do               
            PositionTwo = View[j].Entity:GetComponent(Component.TRANSFORM):GetPosition()

            MassTwo = View[j].Mass

            Distance = (PositionOne - PositionTwo):Length()

            Force = ((BigG) / ((Distance * Distance)))
            Direction = (PositionTwo - PositionOne) / Distance

            View[i].Velocity = View[i].Velocity + Direction * Force * TimeUnit * MassTwo
            View[j].Velocity = View[j].Velocity - Direction * Force * TimeUnit * MassOne
        end        
       
        Transform:AddPosition(View[i].Velocity * TimeUnit)
    end
end

return Controller