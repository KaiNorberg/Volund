local ShowFPS = {}

function ShowFPS:OnUpdate(TimeStep)
    Print(1.0 / TimeStep)
end

return ShowFPS