#pragma once

#include "Renderer/Shader/Shader.h"

#include "Container/Container.h"

#include "MaterialValue.h"

namespace Volund
{
	class Material
	{
	public:

		template <typename T>
		const std::vector<Ref<MaterialValue<T>>> View() const;

		template <typename T>
		T Get(const std::string& Name) const;

		template <typename T>
		void Set(const std::string& Name, T Value);

		void UpdateShader();

		Ref<Shader> GetShader();

		static Ref<Material> Create(Ref<Shader> ObjectShader);

		Material(Ref<Shader> ObjectShader);

	private:

		Container<BaseMaterialValue> _Container;

		Ref<Shader> _Shader;
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
	inline T Material::Get(const std::string& Name) const
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
	inline void Material::Set(const std::string& Name, T Value)
	{
		this->_Container.PushBack(std::make_shared<MaterialValue<T>>(Name, Value));
	}
}
