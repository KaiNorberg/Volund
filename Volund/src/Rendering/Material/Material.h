#pragma once

#include "Rendering/Shader/Shader.h"
#include "Rendering/Texture/Texture.h"

namespace Volund
{
	class Material
	{
	public:

		void SetInt(const std::string& name, int value);
		void SetDouble(const std::string& name, double value);
		void SetVec2(const std::string& name, const Vec2& value);
		void SetVec3(const std::string& name, const Vec3& value);
		void SetVec4(const std::string& name, const Vec4& value);
		void SetTexture(const std::string& name, Ref<Texture> value);
		void SetFramebuffer(const std::string& name, Ref<Framebuffer> value);

		void SetMatrix(const std::string& name, const Mat4x4& value);

		std::map<std::string, int>& IntMap();
		std::map<std::string, double>& DoubleMap();
		std::map<std::string, Vec2>& Vec2Map();
		std::map<std::string, Vec3>& Vec3Map();
		std::map<std::string, Vec4>& Vec4Map();
		std::map<std::string, Ref<Texture>>& TextureMap();

		void UpdateShader();

		void SetShader(Ref<Shader> shader);
		Ref<Shader> GetShader();

		Ref<MaterialBlueprint> GetBlueprint();

		static Ref<Material> Create();

		static Ref<Material> Create(Ref<Shader> shader);

		Material();

		Material(Ref<Shader> shader);

	private:

		std::map<std::string, int> m_IntUniforms;
		std::map<std::string, double> m_DoubleUniforms;
		std::map<std::string, Vec2> m_Vec2Uniforms;
		std::map<std::string, Vec3> m_Vec3Uniforms;
		std::map<std::string, Vec4> m_Vec4Uniforms;
		std::map<std::string, Ref<Texture>> m_TextureUniforms;
		std::map<std::string, Ref<Framebuffer>> m_FramebufferUniforms;

		std::map<std::string, Mat4x4> m_MatrixUniforms;

		Ref<Shader> m_Shader;

		bool m_MaterialChanged = true;

		void CompareBlueprint();

		void ConformToBlueprint();
	};
}
