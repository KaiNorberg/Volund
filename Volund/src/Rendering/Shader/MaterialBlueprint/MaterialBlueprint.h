#pragma once

namespace Volund
{
	enum class MaterialUniformType
	{
		Int,
		Double,
		Vec2,
		Vec3,
		Vec4,
		Sampler,
		Matrix,
		AMOUNT
	};

	class MaterialBlueprint
	{
	public:

		void AddUniform(const std::string& name, MaterialUniformType type);

		bool ContainsUniform(const std::string& name, MaterialUniformType type);

		const std::vector<std::string>& GetUniforms(MaterialUniformType type) const;

		MaterialBlueprint();

	private:

		std::vector<std::vector<std::string>> m_Uniforms;
	};
}
