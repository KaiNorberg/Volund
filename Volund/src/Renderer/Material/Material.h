#pragma once

#include "Renderer/Shader/Shader.h"
#include "Renderer/Texture/Texture.h"

#include "PolyContainer/PolyContainer.h"

namespace Volund
{
	class Material
	{
	public:

		std::string GetFilepath();

		void SetInt(const std::string& name, int value);

		void SetFloat(const std::string& name, float value);

		void SetDouble(const std::string& name, double value);

		void SetVec2(const std::string& name, const Vec2& value);

		void SetVec3(const std::string& name, const Vec3& value);

		void SetVec4(const std::string& name, const Vec4& value);

		void SetTexture(const std::string& name, Ref<Texture> value);

		void SetFramebuffer(const std::string& name, Ref<Framebuffer> value);

		void UpdateShader();
		Ref<Shader> GetShader();

		static Ref<Material> Create(Ref<Shader> shader);

		Material(Ref<Shader> shader);

	private:

		std::unordered_map<std::string, int> m_IntUniforms;

		std::unordered_map<std::string, float> m_FloatUniforms;

		std::unordered_map<std::string, double> m_DoubleUniforms;

		std::unordered_map<std::string, Vec2> m_Vec2Uniforms;

		std::unordered_map<std::string, Vec3> m_Vec3Uniforms;

		std::unordered_map<std::string, Vec4> m_Vec4Uniforms;

		std::unordered_map<std::string, Ref<Texture>> m_TextureUniforms;

		std::unordered_map<std::string, Ref<Framebuffer>> m_FramebufferUniforms;

		Ref<Shader> m_Shader;

		std::string m_Filepath;
	};
}
