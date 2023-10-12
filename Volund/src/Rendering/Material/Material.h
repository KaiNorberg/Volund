#pragma once

#include "Rendering/Shader/Shader.h"
#include "Rendering/Texture/Texture.h"

#include "SerialTable/SerialTable.h"

namespace Volund
{
	class Material
	{
	public:

		void SetInt(const std::string& name, UniformInt value);
		void SetFloat(const std::string& name, UniformFloat value);
		void SetDouble(const std::string& name, UniformDouble value);
		void SetVec2(const std::string& name, const UniformVec2& value);
		void SetVec3(const std::string& name, const UniformVec3& value);
		void SetVec4(const std::string& name, const UniformVec4& value);
		void SetMat3x3(const std::string& name, const UniformMat3x3& value);
		void SetMat4x4(const std::string& name, const UniformMat4x4& value);
		void SetTexture(const std::string& name, const Ref<Texture>& value);
		void SetFramebuffer(const std::string& name, const Ref<Framebuffer>& value);
		
		void Erase(const std::string& key);

		void Rename(const std::string& key, const std::string& newKey);

		template<typename T>
		bool Is(const std::string& key) const;

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

	template<typename T>
	inline bool Material::Is(const std::string& key) const
	{
		return this->m_Table.Is<T>(key);
	}
}
