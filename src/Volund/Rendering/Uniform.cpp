
#include "Rendering/Uniform.h"

#include "Rendering/Shader.h"

namespace Volund
{
	std::string PrimitiveUniform::GetName() const
	{
		return this->m_name;
	}

	template<>
	void Uniform<IntUniformType>::UpdateShader(std::shared_ptr<Shader> shader)
	{
		shader->SetInt(this->m_name, this->m_value);
	}

	template<>
	void Uniform<FloatUniformType>::UpdateShader(std::shared_ptr<Shader> shader)
	{
		shader->SetFloat(this->m_name, this->m_value);
	}

	template<>
	void Uniform<DoubleUniformType>::UpdateShader(std::shared_ptr<Shader> shader)
	{
		shader->SetDouble(this->m_name, this->m_value);
	}

	template<>
	void Uniform<Vec2UniformType>::UpdateShader(std::shared_ptr<Shader> shader)
	{
		shader->SetVec2(this->m_name, this->m_value);
	}

	template<>
	void Uniform<Vec3UniformType>::UpdateShader(std::shared_ptr<Shader> shader)
	{
		shader->SetVec3(this->m_name, this->m_value);
	}

	template<>
	void Uniform<Vec4UniformType>::UpdateShader(std::shared_ptr<Shader> shader)
	{
		shader->SetVec4(this->m_name, this->m_value);
	}

	template<>
	void Uniform<Mat4x4UniformType>::UpdateShader(std::shared_ptr<Shader> shader)
	{
		shader->SetMat4x4(this->m_name, this->m_value);
	}

	template<>
	void Uniform<TextureUniformType>::UpdateShader(std::shared_ptr<Shader> shader)
	{
		shader->SetTexture(this->m_name, this->m_value);
	}

	template<>
	void Uniform<FramebufferUniformType>::UpdateShader(std::shared_ptr<Shader> shader)
	{
		shader->SetFramebuffer(this->m_name, this->m_value);
	}
}