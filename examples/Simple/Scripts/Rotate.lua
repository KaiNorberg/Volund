local Rotate = 
{
    Number = 5,
    Text = "Hello, World!"
}

function Rotate:OnUpdate(TS)
    X = Vec3:new(0.0, 1.0, 0.0);
    Y = Vec3:new(0.0, 2.0, 0.0);
    print(X.y)
end

return Rotate