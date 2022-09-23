#include "PCH/PCH.h"
#include "Material.h"

#include "VML/VML.h"

#include "AssetLibrary/AssetLibrary.h"

namespace Volund
{
	std::string Material::GetFilepath()
	{
		return this->_Filepath;
	}

	void Material::UpdateShader()
	{
		for (auto& Value : this->View<int>())
		{
			this->_Shader->SetInt(Value->GetName(), Value->GetValue());
		}

		for (auto& Value : this->View<float>())
		{
			this->_Shader->SetFloat(Value->GetName(), Value->GetValue());
		}

		for (auto& Value : this->View<double>())
		{
			this->_Shader->SetDouble(Value->GetName(), Value->GetValue());
		}

		for (auto& Value : this->View<Vec2>())
		{
			this->_Shader->SetVec2(Value->GetName(), Value->GetValue());
		}

		for (auto& Value : this->View<Vec3>())
		{
			this->_Shader->SetVec3(Value->GetName(), Value->GetValue());
		}
	}

	Ref<Shader> Material::GetShader()
	{
		return this->_Shader;
	}

	Ref<Material> Material::Create(std::string_view Filepath)
	{
		VML MaterialVML(Filepath);

		Ref<Shader> ObjectShader = AssetLibrary::Load<Shader>((std::string)MaterialVML.Get("Shader").String());

		Ref<Material> NewMaterial = Material::Create(ObjectShader);
		NewMaterial->_Filepath = Filepath;

		for (auto& [ValueName, Value] : MaterialVML["Values"])
		{
			std::string ValueType = Value.Get("Type");

			if (ValueType == "int")
			{
				NewMaterial->Set(ValueName, (int)Value.Get("Value"));
			}
			else if (ValueType == "float")
			{
				NewMaterial->Set(ValueName, (float)Value.Get("Value"));
			}
			else if (ValueType == "double")
			{
				NewMaterial->Set(ValueName, (double)Value.Get("Value"));
			}
			else if (ValueType == "Vec2")
			{
				VMLEntry Vec2Value = Value.Get("Value");
				NewMaterial->Set(ValueName, Vec2(Vec2Value[0], Vec2Value[1]));
			}
			else if (ValueType == "Vec3" || ValueType == "RGB")
			{
				VMLEntry Vec3Value = Value.Get("Value");
				NewMaterial->Set(ValueName, Vec3(Vec3Value[0], Vec3Value[1], Vec3Value[2]));
			}
			else if (ValueType == "Vec4" || ValueType == "RGBA")
			{
				VMLEntry Vec4Value = Value.Get("Value");
				NewMaterial->Set(ValueName, Vec4(Vec4Value[0], Vec4Value[1], Vec4Value[2], Vec4Value[3]));
			}
			else
			{
				VOLUND_ERROR("Invalid type found in Material Asset (%s)!", Filepath.data());
			}
		}

		return NewMaterial;
	}

	Ref<Material> Material::Create(Ref<Shader> ObjectShader)
	{
		return Ref<Material>(new Material(ObjectShader));
	}

	Material::Material(Ref<Shader> DrawShader)
	{
		this->_Shader = DrawShader;
	}
}
