local PortalScript =
{

}

function PortalScript:OnCreate(Args)
    self.TargetPortal = Args["TargetPortal"]
    self.Player = Args["Player"]
    self.OtherCamera = Scene:CreateEntity()
    self.RenderTexture = Framebuffer:new(Vec2:new(1000, 1000))

    TargetPosition = self.TargetPortal:GetComponent(Component.TRANSFORM):GetPosition()

    self.OtherCamera:AddComponent(Component.TRANSFORM, {Position = TargetPosition, Rotation = Vec3:new(0.0, 0.0, 0.0)})    
    self.OtherCamera:AddComponent(Component.CAMERA, {FOV = 80, TargetBuffer = self.RenderTexture})

    self.OtherCamera:GetComponent(Component.CAMERA):SetLayerMask(2, false)

    self.Entity:GetComponent(Component.MESH_RENDERER, 0):GetMaterial():SetFramebuffer("ColorTexture", self.RenderTexture)
end

function PortalScript:OnRender()    
    ScreenSize = Scene:GetTargetBuffer():GetSize()

    if (ScreenSize.x ~= self.RenderTexture:GetSize().x) then
        self.RenderTexture:Resize(ScreenSize)
    end
end

function PortalScript:OnUpdate(TS)
    SelfPosition = self.Entity:GetComponent(Component.TRANSFORM):GetPosition()
    RelativePosition = self.Player:GetComponent(Component.TRANSFORM):GetPosition() - SelfPosition
    
    NewCameraPos = self.TargetPortal:GetComponent(Component.TRANSFORM):GetPosition() + RelativePosition

    self.OtherCamera:GetComponent(Component.TRANSFORM):SetPosition(NewCameraPos)
    self.OtherCamera:GetComponent(Component.TRANSFORM):SetRotation(self.Player:GetComponent(Component.TRANSFORM):GetRotation())

    ScreenSize = Scene:GetTargetBuffer():GetSize()
    self.Entity:GetComponent(Component.MESH_RENDERER, 0):GetMaterial():SetVec2("ScreenSize", ScreenSize)
end

return PortalScript