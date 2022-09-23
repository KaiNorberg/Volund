#pragma once

#include "Renderer/Shader/Shader.h"

#include "Container/Container.h"

#include "MaterialValue.h"

namespace Volund
{
	class Material
	{
	public:

		std::string GetFilepath();

		template <typename T>
		const std::vector<Ref<MaterialValue<T>>> View() const;

		template <typename T>
		T Get(std::string_view Name) const;

		template <typename T>
		void Set(std::string_view Name, T Value);

		template <typename T>
		void Has(std::string_view Name);

		void UpdateShader();

		Ref<Shader> GetShader();

		static Ref<Material> Create(std::string_view Filepath);

		static Ref<Material> Create(Ref<Shader> ObjectShader);

	private:

		Material(Ref<Shader> ObjectShader);

		Container<BaseMaterialValue> _Container;

		Ref<Shader> _Shader;

		std::string _Filepath;
	};

	template<typename T>
	inline const std::vector<Ref<MaterialValue<T>>> Material::View() const
	{
		if (this->_Container.Contains<MaterialValue<T>>(0))
		{
			auto View = this->_Container.View<MaterialValue<T>>();

			std::vector<Ref<MaterialValue<T>>> Return;
			Return.reserve(View.size());
			for (auto& Value : View)
			{
				Ref<MaterialValue<T>> Temp = std::dynamic_pointer_cast<MaterialValue<T>>(Value);
				Return.push_back(Temp);
			}

			return Return;
		}
		else
		{
			return std::vector<Ref<MaterialValue<T>>>();
		}
	}

	template<typename T>
	inline T Material::Get(std::string_view Name) const
	{
		for (const auto& Value : this->_Container.View<MaterialValue<T>>())
		{
			if (Value->GetName() == Name)
			{
				return *(static_cast<MaterialValue<T>*>(Value));
			}
		}
	}

	template<typename T>
	inline void Material::Set(std::string_view Name, T Value)
	{
		this->_Container.PushBack(std::make_shared<MaterialValue<T>>(Name, Value));
	}

	template<typename T>
	inline void Material::Has(std::string_view Name)
	{
		for (const auto& Value : this->_Container.View<MaterialValue<T>>())
		{
			if (Value->GetName() == Name)
			{
				return true;
			}
		}

		return false;
	}
}
