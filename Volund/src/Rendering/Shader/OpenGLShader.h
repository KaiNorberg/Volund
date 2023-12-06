#pragma once

#include "Shader.h"

namespace Volund
{
	class OpenGLShader : public Shader
	{
	public:

		void Bind() override;

		uint32_t GetId() override;

		bool HasUniform(const std::string& name) override;

		void SetInt(const std::string& name, int value) override;
		void SetFloat(const std::string& name, float value) override;
		void SetDouble(const std::string& name, double value) override;
		void SetVec2(const std::string& name, const Vec2& value) override;
		void SetVec3(const std::string& name, const Vec3& value) override;
		void SetVec4(const std::string& name, const Vec4& value) override;
		//void SetMat3x3(const std::string& name, const Mat3x3& value, bool transpose = false) override;
		void SetMat4x4(const std::string& name, const Mat4x4& value, bool transpose = false) override;
		void SetTexture(const std::string& name, const Ref<Texture>& value) override;
		void SetFramebuffer(const std::string& name, const Ref<Framebuffer>& value) override;

		void Init(const ShaderSource& source, Ref<MaterialBlueprint> materialBlueprint) override;

		const Ref<MaterialBlueprint> GetMaterialBlueprint() override;

		OpenGLShader() = default;

		OpenGLShader(const ShaderSource& source, Ref<MaterialBlueprint> materialBlueprint);

		~OpenGLShader() override;

	private:

		uint32_t CompileShader(uint32_t type, const std::string& source);

		uint32_t GetUniformLocation(const std::string& name);

		std::unordered_map<std::string, uint32_t> m_UniformLocations;

		uint32_t m_Id = 0;

		int32_t m_NextTextureUnit = 0;
		int32_t m_MaxTextureUnit = 0;

		Ref<MaterialBlueprint> m_MaterialBlueprint;
	};
} //namespace Volund
