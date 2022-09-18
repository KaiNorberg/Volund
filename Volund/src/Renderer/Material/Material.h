#pragma once

#include "Renderer/Shader/Shader.h"

#include "Container/Container.h"

#include "MaterialValue.h"

namespace Volund
{
	class Material
	{
	public:

		std::string_view GetFilePath();

		template <typename T>
		const std::vector<Ref<MaterialValue<T>>> View() const;

		template <typename T>
		T Get(std::string_view Name) const;

		template <typename T>
		void Set(std::string_view Name, T Value);

		void UpdateShader();

		Ref<Shader> GetShader();

		static Ref<Material> Create(std::string_view FilePath);

		static Ref<Material> Create(Ref<Shader> ObjectShader);

		Material(Ref<Shader> ObjectShader);

	private:

		Container<BaseMaterialValue> _Container;

		Ref<Shader> _Shader;

		std::string _FilePath;
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
		for (const auto& View : this->_Container)
		{
			for (const auto& Value : View)
			{
				if (Value->GetName() == Name)
				{
					return *(static_cast<MaterialValue<T>*>(Value));
				}
			}
		}
	}

	template<typename T>
	inline void Material::Set(std::string_view Name, T Value)
	{
		this->_Container.PushBack(std::make_shared<MaterialValue<T>>(Name, Value));
	}
}
