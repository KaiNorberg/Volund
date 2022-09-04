#pragma once

#include "Renderer/Mesh/Mesh.h"
#include "Scene/Scene.h"
#include "RenderingAPI/RenderingAPI.h"
#include "Context/Context.h"
#include "Renderer/Shader/Shader.h"
#include "Renderer/Material/Material.h"

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

		Renderer(Ref<Window>& window);

		~Renderer();

	private:		
		
		struct Submission
		{
			Mat4x4 ModelMatrix = Mat4x4(1.0f);
			Ref<Mesh> ObjectMesh;
			Ref<Material> ObjectMaterial;
		};

		static struct SceneData
		{
			Mat4x4 ViewProjMatrix = Mat4x4(1.0f);
			Vec3 EyePosition = Vec3(1.0f);
			std::vector<PointLightData> PointLights;
			std::vector<Submission> Submissions;
		} _SceneData;

		static Ref<RenderingAPI> _RenderingAPI;
		static Ref<Context> _Context;
	};
}

