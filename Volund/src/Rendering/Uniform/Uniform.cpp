#include "PCH/PCH.h"

#include "Uniform.h"

#include "Rendering/Shader/Shader.h"

namespace Volund
{
	std::string PrimitiveUniform::GetName() const
	{
		return this->m_Name;
	}

	void Uniform<IntUniformType>::UpdateShader(Ref<Shader> shader)
	{
		shader->SetInt(this->m_Name, this->m_Value);
	}

	void Uniform<FloatUniformType>::UpdateShader(Ref<Shader> shader)
	{
		shader->SetFloat(this->m_Name, this->m_Value);
	}

	void Uniform<DoubleUniformType>::UpdateShader(Ref<Shader> shader)
	{
		shader->SetDouble(this->m_Name, this->m_Value);
	}

	void Uniform<Vec2UniformType>::UpdateShader(Ref<Shader> shader)
	{
		shader->SetVec2(this->m_Name, this->m_Value);
	}

	void Uniform<Vec3UniformType>::UpdateShader(Ref<Shader> shader)
	{
		shader->SetVec3(this->m_Name, this->m_Value);
	}

	void Uniform<Vec4UniformType>::UpdateShader(Ref<Shader> shader)
	{
		shader->SetVec4(this->m_Name, this->m_Value);
	}

	void Uniform<Mat4x4UniformType>::UpdateShader(Ref<Shader> shader)
	{
		shader->SetMat4x4(this->m_Name, this->m_Value);
	}

	void Uniform<TextureUniformType>::UpdateShader(Ref<Shader> shader)
	{
		shader->SetTexture(this->m_Name, this->m_Value);
	}

	void Uniform<FramebufferUniformType>::UpdateShader(Ref<Shader> shader)
	{
		shader->SetFramebuffer(this->m_Name, this->m_Value);
	}
}