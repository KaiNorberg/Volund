#pragma once

#include "Renderer/Texture/Texture.h"

namespace Volund
{
	class Shader
	{
	public:

		virtual void Bind() = 0;

		virtual bool HasUniform(const std::string& Name) = 0;

		virtual void SetInt(const std::string& Name, int32_t Value) = 0;

		virtual void SetFloat(const std::string& Name, float Value) = 0;

		virtual void SetDouble(const std::string& Name, double Value) = 0;

		virtual void SetVec2(const std::string& Name, const Vec2& Value) = 0;

		virtual void SetVec3(const std::string& Name, const Vec3& Value) = 0;

		virtual void SetVec4(const std::string& Name, const Vec4& Value) = 0;

		virtual void SetMat3x3(const std::string& Name, const Mat3x3& Value, bool Transpose = false) = 0;

		virtual void SetMat4x4(const std::string& Name, const Mat4x4& Value, bool Transpose = false) = 0;

		virtual void SetTexture(const std::string& Name, const Ref<Texture>& Value, uint32_t TextureUnit) = 0;

		static Ref<Shader> Create(const std::string& Filepath);

		static Ref<Shader> Create(const std::string& VertexSource, const std::string& FragmentSource, const std::string& GeometrySource);

		virtual ~Shader() = default;

	protected:

	};
}
