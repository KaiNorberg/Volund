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

		virtual bool HasUniform(std::string_view Name) = 0;

		virtual void SetInt(std::string_view Name, int32_t Value) = 0;

		virtual void SetFloat(std::string_view Name, float Value) = 0;

		virtual void SetDouble(std::string_view Name, double Value) = 0;

		virtual void SetVec2(std::string_view Name, const Vec2& Value) = 0;

		virtual void SetVec3(std::string_view Name, const Vec3& Value) = 0;

		virtual void SetVec4(std::string_view Name, const Vec4& Value) = 0;

		virtual void SetMat3x3(std::string_view Name, const Mat3x3& Value, bool Transpose = false) = 0;

		virtual void SetMat4x4(std::string_view Name, const Mat4x4& Value, bool Transpose = false) = 0;

		static Ref<Shader> CreateFromSource(const std::string& Source);

		static Ref<Shader> Create(const std::string& Filepath);

		static Ref<Shader> Create(std::string_view VertexSource, std::string_view FragmentSource, std::string_view GeometrySource);

		virtual ~Shader() = default;

	protected:

	};
}
