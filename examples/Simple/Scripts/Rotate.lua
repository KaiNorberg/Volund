local Rotate = 
{
    Number = 5,
    Text = "Hello, World!"
}

function Rotate:OnStart()
    print("Rotate OnStart")
end

function Rotate:OnUpdate(TS)
    print("Rotate OnUpdate")
end

function Rotate:OnDestroy()
    print("Rotate OnDestroy")
end

return Rotate