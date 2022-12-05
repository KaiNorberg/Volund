#pragma once

#include "Renderer/Material/Material.h"

namespace Volund
{
	struct LuaMaterial
	{
	public:

		Ref<Material> Get();

		void SetInt(const std::string& Name, lua_Integer Value);

		void SetFloat(const std::string& Name, float Value);

		void SetDouble(const std::string& Name, double Value);

		void SetVec2(const std::string& Name, Vec2 Value);

		void SetVec3(const std::string& Name, Vec3 Value);

		LuaMaterial(Ref<Material> Material);

		LuaMaterial(const std::string& ShaderPath);

	private:

		Ref<Material> _Material;
	};
}