#pragma once

#include "Shader.h"

namespace Volund
{
	class OpenGLShader : public Shader
	{
	public:

		void Bind() override;

		uint32_t GetId() override;

		/// <summary>
		/// Returns if the shader has the specified uniform.
		/// </summary>
		bool HasUniform(const std::string& name) override;

		/// <summary>
		/// Sets a int shader uniform.
		/// </summary>
		void SetInt(const std::string& name, int32_t value) override;

		/// <summary>
		/// Sets a float shader uniform.
		/// </summary>
		void SetFloat(const std::string& name, float value) override;

		/// <summary>
		/// Sets a double shader uniform.
		/// </summary>
		void SetDouble(const std::string& name, double value) override;

		/// <summary>
		/// Sets a vector2 shader uniform.
		/// </summary>
		void SetVec2(const std::string& name, const Vec2& value) override;

		/// <summary>
		/// Sets a vector3 shader uniform.
		/// </summary>
		void SetVec3(const std::string& name, const Vec3& value) override;

		/// <summary>
		/// Sets a vector4 shader uniform.
		/// </summary>
		void SetVec4(const std::string& name, const Vec4& value) override;

		/// <summary>
		/// Sets a matrix3 shader uniform.
		/// </summary>
		void SetMat3x3(const std::string& name, const Mat3x3& value, bool transpose = false) override;

		/// <summary>
		/// Sets a matrix4 shader uniform.
		/// </summary>
		void SetMat4x4(const std::string& name, const Mat4x4& value, bool transpose = false) override;

		void SetTexture(const std::string& name, const Ref<Texture>& value, uint32_t textureUnit) override;

		void SetFramebuffer(const std::string& name, const Ref<Framebuffer>& value, uint32_t textureUnit) override;

		void Init(const ShaderSource& source, Ref<MaterialBlueprint> materialBlueprint) override;

		OpenGLShader() = default;

		OpenGLShader(const ShaderSource& source, Ref<MaterialBlueprint> materialBlueprint);

		~OpenGLShader() override;

	private:
		uint32_t CompileShader(uint32_t type, const std::string& source);

		uint32_t GetUniformLocation(const std::string& name);

		std::unordered_map<std::string, uint32_t> m_UniformLocations;

		uint32_t m_Id = 0;
	};
} //namespace Volund
