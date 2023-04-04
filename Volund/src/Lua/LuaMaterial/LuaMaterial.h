#pragma once

#include "Renderer/Material/Material.h"

#include "Lua/LuaShader/LuaShader.h"
#include "Lua/LuaTexture/LuaTexture.h"
#include "Lua/LuaFramebuffer/LuaFramebuffer.h"

namespace Volund
{
	struct LuaMaterial
	{
	public:

		int Padding = 0;

		Ref<Material> Get();

		void SetInt(const std::string& name, int value);

		void SetFloat(const std::string& name, float value);

		void SetDouble(const std::string& name, double value);

		void SetVec2(const std::string& name, Vec2 value);

		void SetVec3(const std::string& name, Vec3 value);

		void SetTexture(const std::string& name, LuaTexture value);

		void SetFramebuffer(const std::string& name, LuaFramebuffer value);

		LuaMaterial(Ref<Material> material);

		LuaMaterial(LuaShader shader);

	private:

		Ref<Material> m_Material;
	};
}