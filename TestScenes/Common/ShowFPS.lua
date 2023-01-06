local ShowFPS = 
{
    TotalTime = 5.0,
    Iter = 0,
    MaxTimeStep = 0.0
}

function ShowFPS:OnUpdate(TimeStep)
    self.TotalTime = self.TotalTime + TimeStep
    self.Iter = self.Iter + 1
    self.MaxTimeStep = math.max(self.MaxTimeStep, TimeStep)
    if self.TotalTime >= 1 then
        print("FPS: " .. self.Iter .. " Min: " .. 1 / self.MaxTimeStep)
        self.Iter = 0
        self.TotalTime = 0.0
        self.MaxTimeStep = 0
    end
end

return ShowFPS