#pragma once

#include "SerialTable/SerialTable.h"

namespace Volund
{
	class MaterialBlueprint
	{
	private:

		class BlueprintUniform
		{
		public:

			uint64_t GetTypeHash() const;

			const std::string& GetName() const;

			template<typename T>
			bool Is() const;

			BlueprintUniform(uint64_t typeHash, const std::string& name);

		private:

			uint64_t m_TypeHash;

			std::string m_Name;
		};

	public:

		template<typename T>
		void Insert(const std::string& name);

		template<typename T>
		bool Contains(const std::string& name);

		bool Exists(const std::string& name);

		const std::vector<BlueprintUniform>::const_iterator begin() const;
		const std::vector<BlueprintUniform>::const_iterator end() const;

	private:

		std::vector<BlueprintUniform> m_Uniforms;
	};

	template<typename T>
	inline bool MaterialBlueprint::BlueprintUniform::Is() const
	{
		constexpr uint64_t typeHash = typeid(T).hash_code();

		return this->m_TypeHash == typeHash;
	}

	template<typename T>
	inline void MaterialBlueprint::Insert(const std::string& name)
	{
		this->m_Uniforms.push_back(BlueprintUniform(typeid(T).hash_code(), name));
	}

	template<typename T>
	inline bool MaterialBlueprint::Contains(const std::string& name)
	{
		constexpr uint64_t typeHash = typeid(T).hash_code();

		for (auto& uniform : this->m_Uniforms)
		{
			if (uniform.GetTypeHash() == typeHash && uniform.GetName() == name)
			{
				return true;
			}
		}

		return false;
	}
}
