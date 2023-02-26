#pragma once

#include "Renderer/Shader/Shader.h"
#include "Renderer/Texture/Texture.h"

#include "Container/Container.h"

#include "MaterialValue.h"

namespace Volund
{
	class Material
	{
	public:

		std::string GetFilepath();

		void SetInt(const std::string& Name, int Value);

		void SetFloat(const std::string& Name, float Value);

		void SetDouble(const std::string& Name, double Value);

		void SetVec2(const std::string& Name, const Vec2& Value);

		void SetVec3(const std::string& Name, const Vec3& Value);

		void SetTexture(const std::string& Name, Ref<Texture> Value);

		void SetFramebuffer(const std::string& Name, Ref<Framebuffer> Value);

		void UpdateShader();
		Ref<Shader> GetShader();

		static Ref<Material> Create(Ref<Shader> ObjectShader);

		Material(Ref<Shader> ObjectShader);

	private:

		std::unordered_map<std::string, int> _IntUniforms;

		std::unordered_map<std::string, float> _FloatUniforms;

		std::unordered_map<std::string, double> _DoubleUniforms;

		std::unordered_map<std::string, Vec2> _Vec2Uniforms;

		std::unordered_map<std::string, Vec3> _Vec3Uniforms;

		std::unordered_map<std::string, Ref<Texture>> _TextureUniforms;

		std::unordered_map<std::string, Ref<Framebuffer>> _FramebufferUniforms;

		Ref<Shader> _Shader;

		std::string _Filepath;
	};
}
