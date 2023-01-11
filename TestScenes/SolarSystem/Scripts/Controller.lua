Gravity = require("Scripts/Gravity.lua")

TimeUnit = 10^6 --Some number

BigG = 6.674 * 10^-11

local Controller = 
{
    GravityView = nil
}

function Controller:OnCreate(Args)
    self.GravityView = Scene:View(Gravity)

    StarMass = self.GravityView[1].Mass
    for i = 2, #self.GravityView do           
        Position = self.GravityView[i].Entity:GetComponent(Component.TRANSFORM):GetPosition()

        Speed = math.sqrt((BigG * StarMass) / (Position:Length()))

        Direction = (Vec3:new(0.0) - Position):Normalize()

        self.GravityView[i].Velocity = Direction:Cross(Vec3:new(0, 1, 0)):Normalize() * (Speed)
    end
end

function Controller:OnUpdate(TimeStep)
    for i = 1, #self.GravityView do    
        Transform = self.GravityView[i].Entity:GetComponent(Component.TRANSFORM)

        PositionOne = Transform:GetPosition()
        MassOne = self.GravityView[i].Mass 

        for j = i + 1, #self.GravityView do               
            PositionTwo = self.GravityView[j].Entity:GetComponent(Component.TRANSFORM):GetPosition()
            MassTwo = self.GravityView[j].Mass

            Delta = PositionOne - PositionTwo

            Distance2 = Delta:Length2()

            ForceConstant = BigG / Distance2
            Direction = Delta / math.sqrt(Distance2)

            self.GravityView[i].Velocity = self.GravityView[i].Velocity - Direction * ForceConstant * TimeUnit * MassTwo
            self.GravityView[j].Velocity = self.GravityView[j].Velocity + Direction * ForceConstant * TimeUnit * MassOne
        end        
       
        Transform:AddPosition(self.GravityView[i].Velocity * TimeUnit)
    end
end

return Controller