local PortalScript =
{

}

function PortalScript:OnCreate(Args)
    self.TargetPortal = Args["TargetPortal"]
    self.Player = Args["Player"]
    self.OtherCamera = Scene:CreateEntity()
    self.RenderTexture = Framebuffer:new(Vec2:new(1000, 1000))

    TargetPosition = self.TargetPortal:Get(Component.TRANSFORM):GetPosition()

    self.OtherCamera:Add(Component.TRANSFORM, {Position = TargetPosition, Rotation = Vec3:new(0.0, 0.0, 0.0)})    
    self.OtherCamera:Add(Component.CAMERA, {FOV = 80, TargetBuffer = self.RenderTexture})

    self.OtherCamera:Get(Component.CAMERA):SetLayerMask(2, false)

    self.Entity:Get(Component.MESH_RENDERER, 0):GetMaterial():SetFramebuffer("ColorTexture", self.RenderTexture)
end

function PortalScript:OnRender()    
    ScreenSize = Scene:GetTargetBuffer():GetSize()

    if (ScreenSize.x ~= self.RenderTexture:GetSize().x) then
        self.RenderTexture:Resize(ScreenSize)
    end

    SelfPosition = self.Entity:Get(Component.TRANSFORM):GetPosition()
    RelativePosition = self.Player:Get(Component.TRANSFORM):GetPosition() - SelfPosition
    
    NewCameraPos = self.TargetPortal:Get(Component.TRANSFORM):GetPosition() + RelativePosition

    self.OtherCamera:Get(Component.TRANSFORM):SetPosition(NewCameraPos)
    self.OtherCamera:Get(Component.TRANSFORM):SetRotation(self.Player:Get(Component.TRANSFORM):GetRotation())
    
    self.Entity:Get(Component.MESH_RENDERER, 0):GetMaterial():SetVec2("ScreenSize", ScreenSize)
end

return PortalScript