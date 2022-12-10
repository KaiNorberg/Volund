#pragma once

#include "Renderer/Material/Material.h"

#include "Core/Lua/LuaShader/LuaShader.h"
#include "Core/Lua/LuaTexture/LuaTexture.h"

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

		void SetTexture(const std::string& Name, LuaTexture& Value);

		LuaMaterial(Ref<Material> Material);

		LuaMaterial(LuaShader MaterialShader);

	private:

		Ref<Material> _Material;
	};
}