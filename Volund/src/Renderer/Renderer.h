#pragma once

#include "Renderer/Mesh/Mesh.h"
#include "Scene/Scene.h"
#include "RenderingAPI/RenderingAPI.h"
#include "Context/Context.h"
#include "Shader/Shader.h"
#include "Material/Material.h"
#include "Texture/Texture.h"

namespace Volund
{
	struct PointLightData
	{
		RGB Color;
		Vec3 Position;
	};

	class Renderer
	{
	public:

		static void BeginScene(Mat4x4& ViewProjMatrix, Vec3& EyePosition, std::vector<PointLightData> const& PointLights);
		static void EndScene();

		static void Submit(Mat4x4& ModelMatrix, Ref<Mesh> const& ObjectMesh, Ref<Material> const& ObjectMaterial);

		static Ref<Window> GetWindow();

		static void SetWindow(Ref<Window> const& NewWindow);

	private:		
		
		struct Submission
		{
			Mat4x4 ModelMatrix = Mat4x4(1.0f);
			Ref<Mesh> ObjectMesh;
			Ref<Material> ObjectMaterial;
		};

		static inline struct SceneData
		{
			Mat4x4 ViewProjMatrix = Mat4x4(1.0f);
			Vec3 EyePosition = Vec3(1.0f);
			std::vector<PointLightData> PointLights;
			std::vector<Submission> Submissions;
		} _SceneData;

		static inline Ref<RenderingAPI> _RenderingAPI;
		static inline Ref<Context> _Context;
		static inline Ref<Window> _Window;
	};
}

