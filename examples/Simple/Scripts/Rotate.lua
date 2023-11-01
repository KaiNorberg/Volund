local Rotate = 
{
    Integer = 5,
    Float = 3.14
}

function Rotate:OnStart()
    self.First = false
    print("Rotate OnStart")
end

function Rotate:OnUpdate(TS)
    if self.First then
        print("Rotate OnUpdate")
        self.First = false
    end
end

function Rotate:OnDestroy()
    print("Rotate OnDestroy")
end

return Rotate