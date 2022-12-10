#include "PCH/PCH.h"
#include "LuaMaterial.h"

namespace Volund
{
	Ref<Material> LuaMaterial::Get()
	{
		return this->_Material;
	}

	void LuaMaterial::SetInt(const std::string& Name, lua_Integer Value)
	{
		this->_Material->Set(Name, (int)Value);
	}

	void LuaMaterial::SetFloat(const std::string& Name, float Value)
	{
		this->_Material->Set(Name, Value);
	}

	void LuaMaterial::SetDouble(const std::string& Name, double Value)
	{
		this->_Material->Set(Name, Value);
	}

	void LuaMaterial::SetVec2(const std::string& Name, Vec2 Value)
	{
		this->_Material->Set(Name, Value);
	}

	void LuaMaterial::SetVec3(const std::string& Name, Vec3 Value)
	{
		this->_Material->Set(Name, Value);
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