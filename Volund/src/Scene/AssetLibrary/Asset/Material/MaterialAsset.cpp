#include "PCH/PCH.h"
#include "MaterialAsset.h"

#include "Scene/AssetLibrary/Asset/Shader/ShaderAsset.h"

namespace Volund
{
	Ref<Material> MaterialAsset::Get()
	{
		return this->_Material;
	}

	MaterialAsset::MaterialAsset(AssetLibrary* Parent, const std::string& FilePath)
	{
		this->_Parent = Parent;

		this->_FilePath = FilePath;

		VML MaterialVML(FilePath);

		Ref<Shader> ObjectShader = Parent->Get<ShaderAsset>(MaterialVML.Get("Shader").GetAs<std::string>())->Get();

		this->_Material = Material::Create(ObjectShader);

		for (auto& [ValueName, Value] : MaterialVML["Values"])
		{
			std::string ValueType = Value.Get("Type");

			if (ValueType == "int")
			{
				this->_Material->Set(ValueName, (int)Value.Get("Value"));
			}
			else if (ValueType == "float")
			{
				this->_Material->Set(ValueName, (float)Value.Get("Value"));
			}
			else if (ValueType == "Vec2")
			{
				VMLEntry Vec2Value = Value.Get("Value");
				this->_Material->Set(ValueName, Vec2(Vec2Value[0], Vec2Value[1]));
			}
			else if (ValueType == "Vec3" || ValueType == "RGB")
			{
				VMLEntry Vec3Value = Value.Get("Value");
				this->_Material->Set(ValueName, Vec3(Vec3Value[0], Vec3Value[1], Vec3Value[2]));
			}
			else if (ValueType == "Vec4" || ValueType == "RGBA")
			{
				VMLEntry Vec4Value = Value.Get("Value");
				this->_Material->Set(ValueName, Vec4(Vec4Value[0], Vec4Value[1], Vec4Value[2], Vec4Value[3]));
			}
			else
			{
				VOLUND_ERROR("Invalid type found in Material Asset (%s)!", FilePath.c_str());
			}
		}
	}
}
