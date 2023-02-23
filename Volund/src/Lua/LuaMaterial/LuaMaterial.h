#pragma once

#include "Renderer/Material/Material.h"

#include "Lua/LuaShader/LuaShader.h"
#include "Lua/LuaTexture/LuaTexture.h"

namespace Volund
{
	struct LuaMaterial
	{
	public:

		int Padding = NULL;

		Ref<Material> Get();

		void SetInt(const std::string& Name, int Value);

		void SetFloat(const std::string& Name, float Value);

		void SetDouble(const std::string& Name, double Value);

		void SetVec2(const std::string& Name, Vec2 Value);

		void SetVec3(const std::string& Name, Vec3 Value);

		void SetTexture(const std::string& Name, LuaTexture Value);

		LuaMaterial(Ref<Material> Material);

		LuaMaterial(LuaShader MaterialShader);

	private:

		Ref<Material> _Material;
	};
}