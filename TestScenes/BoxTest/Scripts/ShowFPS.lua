local ShowFPS = 
{
    TotalTime = 0.0,
    Iter = 0
}

function ShowFPS:OnUpdate(TimeStep)
    self.TotalTime = self.TotalTime + TimeStep
    self.Iter = self.Iter + 1
    if self.TotalTime >= 1 then
        print("FPS: " .. self.Iter)
        self.Iter = 0
        self.TotalTime = 0.0
    end
end

return ShowFPS