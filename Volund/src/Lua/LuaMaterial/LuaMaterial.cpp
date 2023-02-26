#include "PCH/PCH.h"
#include "LuaMaterial.h"

namespace Volund
{
	Ref<Material> LuaMaterial::Get()
	{
		return this->_Material;
	}

	void LuaMaterial::SetInt(const std::string& Name, int Value)
	{
		this->_Material->SetInt(Name, Value);
	}

	void LuaMaterial::SetFloat(const std::string& Name, float Value)
	{
		this->_Material->SetFloat(Name, Value);
	}

	void LuaMaterial::SetDouble(const std::string& Name, double Value)
	{
		this->_Material->SetDouble(Name, Value);
	}

	void LuaMaterial::SetVec2(const std::string& Name, Vec2 Value)
	{
		this->_Material->SetVec2(Name, Value);
	}

	void LuaMaterial::SetVec3(const std::string& Name, Vec3 Value)
	{
		this->_Material->SetVec3(Name, Value);
	}

	void LuaMaterial::SetTexture(const std::string& Name, LuaTexture Value)
	{
		this->_Material->SetTexture(Name, Value.Get());
	}

	void LuaMaterial::SetFramebuffer(const std::string& Name, LuaFramebuffer Value)
	{
		this->_Material->SetFramebuffer(Name, Value.Get());
	}

	LuaMaterial::LuaMaterial(Ref<Material> Material)
	{
		this->_Material = Material;
	}

	LuaMaterial::LuaMaterial(LuaShader MaterialShader)
	{
		this->_Material = Material::Create(MaterialShader.Get());
	}
}