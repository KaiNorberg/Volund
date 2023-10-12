#pragma once

#include "Rendering/Texture/Texture.h"
#include "Rendering/Framebuffer/Framebuffer.h"

#include "ResourceLibrary/ResourceLibrary.h"

#include "MaterialBlueprint/MaterialBlueprint.h"

#include "ShaderLoader/ShaderLoader.h"

namespace Volund
{
	using UniformInt = int;
	using UniformFloat = float;
	using UniformDouble = double;
	using UniformVec2 = Vec2;
	using UniformVec3 = Vec3;
	using UniformVec4 = Vec4;
	using UniformMat3x3 = Mat3x3;
	using UniformMat4x4 = Mat4x4;
	using UniformTexture = Ref<Texture>;
	using UniformFramebuffer = Ref<Framebuffer>;

	class Shader
	{
	public:

		virtual void Bind() = 0;

		virtual bool HasUniform(const std::string& name) = 0;

		virtual uint32_t GetId() = 0;

		virtual void SetInt(const std::string& name, UniformInt value) = 0;
		virtual void SetFloat(const std::string& name, UniformFloat value) = 0;
		virtual void SetDouble(const std::string& name, UniformDouble value) = 0;
		virtual void SetVec2(const std::string& name, const UniformVec2& value) = 0;
		virtual void SetVec3(const std::string& name, const UniformVec3& value) = 0;
		virtual void SetVec4(const std::string& name, const UniformVec4& value) = 0;
		virtual void SetMat3x3(const std::string& name, const UniformMat3x3& value, bool transpose = false) = 0;
		virtual void SetMat4x4(const std::string& name, const UniformMat4x4& value, bool transpose = false) = 0;
		virtual void SetTexture(const std::string& name, const UniformTexture& value, uint32_t textureUnit) = 0;
		virtual void SetFramebuffer(const std::string& name, const UniformFramebuffer& value, uint32_t textureUnit) = 0;

		virtual void Init(const ShaderSource& source, Ref<MaterialBlueprint> materialBlueprint) = 0;

		const Ref<MaterialBlueprint> GetMaterialBlueprint();

		static Ref<Shader> Create();

		static Ref<Shader> Create(const std::string& filepath);

		static Ref<Shader> Create(const ShaderSource& source, Ref<MaterialBlueprint> materialBlueprint);

		virtual ~Shader() = default;

	protected:

		Shader();

		Ref<MaterialBlueprint> m_MaterialBlueprint;
	};
}
