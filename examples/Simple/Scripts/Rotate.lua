local Rotate = 
{
    Number = 5,
    Text = "Hello, World!",
    Vector2 = Vec2:new(1.0, 2.0),
    Vector3 = Vec3:new(3.0, 4.0, 5.0),
    Vector4 = Vec4:new(6.0, 7.0, 8.0, 9.0)
}

function Rotate:OnStart()
    print("Rotate OnStart")
end

function Rotate:OnUpdate(TS)
    --print(self.Vector3.y)
end

return Rotate