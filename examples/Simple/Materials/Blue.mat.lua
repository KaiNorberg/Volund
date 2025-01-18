--[[
local table =
{
	FileType = "Material",
	Data = 
	{
		Shader = "://Simple.shader",
		Uniforms =
		{
			Albedo = Vec3:new(0.000000, 0.000000, 1.000000),
			Metallic = 0.700000,
			Ambient = Vec3:new(0.000000, 0.000000, 0.000000),
			Roughness = 0.700000
		}
	}
}

return table]]--



material = Material.new()