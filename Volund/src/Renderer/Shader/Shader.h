#pragma once

namespace Volund
{
	/// <summary>
	/// A shader object that Contains code that describes how to render a mesh to the screen.
	/// </summary>
	class Shader
	{
	public:

		virtual void Bind() = 0;

		/// <summary>
		/// Returns if the shader has the specified uniform.
		/// </summary>
		virtual bool HasUniform(std::string_view Name) = 0;

		/// <summary>
		/// Sets a int shader uniform.
		/// </summary>
		virtual void SetInt(std::string_view Name, int32_t Value) = 0;

		/// <summary>
		/// Sets a float shader uniform.
		/// </summary>
		virtual void SetFloat(std::string_view Name, float Value) = 0;

		/// <summary>
		/// Sets a double shader uniform.
		/// </summary>
		virtual void SetDouble(std::string_view Name, double Value) = 0;

		/// <summary>
		/// Sets a vector2 shader uniform.
		/// </summary>
		virtual void SetVec2(std::string_view Name, const Vec2& Value) = 0;

		/// <summary>
		/// Sets a vector3 shader uniform.
		/// </summary>
		virtual void SetVec3(std::string_view Name, const Vec3& Value) = 0;

		/// <summary>
		/// Sets a vector4 shader uniform.
		/// </summary>
		virtual void SetVec4(std::string_view Name, const Vec4& Value) = 0;

		/// <summary>
		/// Sets a matrix3 shader uniform.
		/// </summary>
		virtual void SetMat3x3(std::string_view Name, const Mat3x3& Value, bool Transpose = false) = 0;

		/// <summary>
		/// Sets a matrix4 shader uniform.
		/// </summary>
		virtual void SetMat4x4(std::string_view Name, const Mat4x4& Value, bool Transpose = false) = 0;

		static Ref<Shader> Create(std::string_view VertexSource, std::string_view FragmentSource, std::string_view GeometrySource);

		virtual ~Shader() = default;

	protected:

	};
} //namespace Volund
