#pragma once

#include "Shader.h"

namespace Volund
{
	class OpenGLShader : public Shader
	{
	public:
		void Bind() override;

		/// <summary>
		/// Returns if the shader has the specified uniform.
		/// </summary>
		bool HasUniform(std::string_view Name) override;

		/// <summary>
		/// Sets a int shader uniform.
		/// </summary>
		void SetInt(std::string_view Name, int32_t Value) override;

		/// <summary>
		/// Sets a float shader uniform.
		/// </summary>
		void SetFloat(std::string_view Name, float Value) override;

		/// <summary>
		/// Sets a double shader uniform.
		/// </summary>
		void SetDouble(std::string_view Name, double Value) override;

		/// <summary>
		/// Sets a vector2 shader uniform.
		/// </summary>
		void SetVec2(std::string_view Name, const Vec2& Value) override;

		/// <summary>
		/// Sets a vector3 shader uniform.
		/// </summary>
		void SetVec3(std::string_view Name, const Vec3& Value) override;

		/// <summary>
		/// Sets a vector4 shader uniform.
		/// </summary>
		void SetVec4(std::string_view Name, const Vec4& Value) override;

		/// <summary>
		/// Sets a matrix3 shader uniform.
		/// </summary>
		void SetMat3x3(std::string_view Name, const Mat3x3& Value, bool Transpose = false) override;

		/// <summary>
		/// Sets a matrix4 shader uniform.
		/// </summary>
		void SetMat4x4(std::string_view Name, const Mat4x4& Value, bool Transpose = false) override;

		void SetTexture(std::string_view Name, const Ref<Texture>& Value, uint32_t TextureUnit) override;

		OpenGLShader() = default;

		OpenGLShader(std::string_view VertexSource, std::string_view FragmentSource, std::string_view GeometrySource);

		~OpenGLShader() override;

	private:
		uint32_t CompileShader(uint32_t Type, std::string_view Source);

		uint32_t GetUniformLocation(std::string_view Name);

		std::unordered_map<std::string, uint32_t> UniformLocations;

		uint32_t ID = 0;
	};
} //namespace Volund
