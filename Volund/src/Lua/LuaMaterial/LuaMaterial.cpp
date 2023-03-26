#include "PCH/PCH.h"
#include "LuaMaterial.h"

namespace Volund
{
	Ref<Material> LuaMaterial::Get()
	{
		return this->m_Material;
	}

	void LuaMaterial::SetInt(const std::string& name, int value)
	{
		this->m_Material->SetInt(name, value);
	}

	void LuaMaterial::SetFloat(const std::string& name, float value)
	{
		this->m_Material->SetFloat(name, value);
	}

	void LuaMaterial::SetDouble(const std::string& name, double value)
	{
		this->m_Material->SetDouble(name, value);
	}

	void LuaMaterial::SetVec2(const std::string& name, Vec2 value)
	{
		this->m_Material->SetVec2(name, value);
	}

	void LuaMaterial::SetVec3(const std::string& name, Vec3 value)
	{
		this->m_Material->SetVec3(name, value);
	}

	void LuaMaterial::SetTexture(const std::string& name, LuaTexture value)
	{
		this->m_Material->SetTexture(name, value.Get());
	}

	void LuaMaterial::SetFramebuffer(const std::string& name, LuaFramebuffer value)
	{
		this->m_Material->SetFramebuffer(name, value.Get());
	}

	LuaMaterial::LuaMaterial(Ref<Material> material)
	{
		this->m_Material = material;
	}

	LuaMaterial::LuaMaterial(LuaShader shader)
	{
		this->m_Material = Material::Create(shader.Get());
	}
}