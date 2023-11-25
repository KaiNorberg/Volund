local Rotate = 
{
    Integer = 5,
    Float = 3.14
}

function Rotate:OnStart()

end

function Rotate:OnUpdate(TS)
    print(self.Entity)
end

function Rotate:OnDestroy()
    
end

return Rotate