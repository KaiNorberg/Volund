#pragma once

namespace Volund
{
	/// <summary>
	/// A shader object that Contains code that describes how to render a mesh to the screen.
	/// </summary>
	class Shader
	{
	public:
		std::string GetFilePath();

		virtual void Bind() = 0;

		/// <summary>
		/// Returns if the shader has the specified uniform.
		/// </summary>
		virtual bool HasUniform(const std::string& Name) = 0;

		/// <summary>
		/// Sets a int shader uniform.
		/// </summary>
		virtual void SetInt(const std::string& Name, int32_t Value) = 0;

		/// <summary>
		/// Sets a float shader uniform.
		/// </summary>
		virtual void SetFloat(const std::string& Name, float Value) = 0;

		/// <summary>
		/// Sets a double shader uniform.
		/// </summary>
		virtual void SetDouble(const std::string& Name, float Value) = 0;

		/// <summary>
		/// Sets a vector2 shader uniform.
		/// </summary>
		virtual void SetVec2(const std::string& Name, const Vec2& Value) = 0;

		/// <summary>
		/// Sets a vector3 shader uniform.
		/// </summary>
		virtual void SetVec3(const std::string& Name, const Vec3& Value) = 0;

		/// <summary>
		/// Sets a vector4 shader uniform.
		/// </summary>
		virtual void SetVec4(const std::string& Name, const Vec4& Value) = 0;

		/// <summary>
		/// Sets a matrix3 shader uniform.
		/// </summary>
		virtual void SetMat3x3(const std::string& Name, const Mat3x3& Value, bool Transpose = false) = 0;

		/// <summary>
		/// Sets a matrix4 shader uniform.
		/// </summary>
		virtual void SetMat4x4(const std::string& Name, const Mat4x4& Value, bool Transpose = false) = 0;

		static Ref<Shader> Create(const std::string& FilePath);

		virtual ~Shader() = default;

	protected:
		struct Source
		{
			std::string VertexSource;

			std::string FragmentSource;

			std::string GeometrySource;
		};

		Source ParseShader(const std::string& FilePath) const;

		std::string _FilePath;
	};
} //namespace Volund
