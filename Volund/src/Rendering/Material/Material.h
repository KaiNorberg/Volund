#pragma once

#include "Rendering/Shader/Shader.h"
#include "Rendering/Texture/Texture.h"

#include "SerialTable/SerialTable.h"

namespace Volund
{
	class Material
	{
	public:

		template<typename T, VOLUND_TEMPLATE_UNIFORM_TYPES_ONLY>
		void Set(const std::string& name, const T& value);
		
		template<typename T, VOLUND_TEMPLATE_UNIFORM_TYPES_ONLY>
		bool Is(const std::string& key) const;

		void Erase(const std::string& key);

		void Rename(const std::string& key, const std::string& newKey);

		const SerialTable::const_iterator begin() const;
		const SerialTable::const_iterator end() const;

		SerialTable::iterator begin();
		SerialTable::iterator end();

		void SetShader(Ref<Shader> shader);
		Ref<Shader> GetShader();

		Ref<MaterialBlueprint> GetBlueprint();

		void UpdateShader();

		static Ref<Material> Create();
		static Ref<Material> Create(Ref<Shader> shader);

		Material();

		Material(Ref<Shader> shader);

	private:

		SerialTable m_Table;

		Ref<Shader> m_Shader;

		Ref<MaterialBlueprint> m_Blueprint;

		bool m_MaterialChanged = true;

		void CompareBlueprint();

		void ConformToBlueprint();
	};

	template<typename T, typename>
	inline void Material::Set(const std::string& name, const T& value)
	{
		if (this->m_Table.Contains<T>(name))
		{
			this->m_Table[name] = value;
		}
		else
		{
			this->m_Table.Insert(name, value);
		}
	}

	template<typename T, typename>
	inline bool Material::Is(const std::string& key) const
	{
		return this->m_Table.Is<T>(key);
	}
}
