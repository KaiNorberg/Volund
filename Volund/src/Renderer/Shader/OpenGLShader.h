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
		bool HasUniform(const std::string& Name) override;

		/// <summary>
		/// Sets a int shader uniform.
		/// </summary>
		void SetInt(const std::string& Name, int32_t Value) override;

		/// <summary>
		/// Sets a float shader uniform.
		/// </summary>
		void SetFloat(const std::string& Name, float Value) override;

		/// <summary>
		/// Sets a double shader uniform.
		/// </summary>
		void SetDouble(const std::string& Name, double Value) override;

		/// <summary>
		/// Sets a vector2 shader uniform.
		/// </summary>
		void SetVec2(const std::string& Name, const Vec2& Value) override;

		/// <summary>
		/// Sets a vector3 shader uniform.
		/// </summary>
		void SetVec3(const std::string& Name, const Vec3& Value) override;

		/// <summary>
		/// Sets a vector4 shader uniform.
		/// </summary>
		void SetVec4(const std::string& Name, const Vec4& Value) override;

		/// <summary>
		/// Sets a matrix3 shader uniform.
		/// </summary>
		void SetMat3x3(const std::string& Name, const Mat3x3& Value, bool Transpose = false) override;

		/// <summary>
		/// Sets a matrix4 shader uniform.
		/// </summary>
		void SetMat4x4(const std::string& Name, const Mat4x4& Value, bool Transpose = false) override;

		OpenGLShader() = default;

		OpenGLShader(const std::string& VertexSource, const std::string& FragmentSource, const std::string& GeometrySource);

		~OpenGLShader() override;

	private:
		uint32_t CompileShader(uint32_t Type, const std::string& Source);

		uint32_t GetUniformLocation(const std::string& Name);

		std::unordered_map<std::string, uint32_t> UniformLocations;

		uint32_t ID = 0;
	};
} //namespace Volund
