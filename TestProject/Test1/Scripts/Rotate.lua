
function Update(Entity, TS)
    Entity:GetComponent(Component.TRANSFORM):AddRotation(Vec3:new(0.0, 90.0 * TS, 0.0))
end