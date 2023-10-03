local Rotate = 
{
    Number = 5,
    Text = "Hello, World!"
}

function Rotate:OnStart()
    print("Rotate OnStart")
end

function Rotate:OnUpdate(TS)
    --print(self.Vector3.y)
end

return Rotate