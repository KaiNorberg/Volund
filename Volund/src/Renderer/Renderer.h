#pragma once

#include "Renderer/Mesh/Mesh.h"
#include "Scene/Scene.h"
#include "RenderingAPI/RenderingAPI.h"
#include "Context/Context.h"
#include "Shader/Shader.h"
#include "Material/Material.h"
#include "Texture/Texture.h"

#include "Window/Window.h"

namespace Volund
{
	class PointLight;
	struct PointLightData
	{
		RGB Color;
		float Brightness;
		Vec3 Position;
	};

	class Renderer
	{
	public:

		static void BeginScene(Mat4x4& ViewProjMatrix, Vec3& EyePosition, const std::vector<PointLightData>& PointLights);	

		static void BeginScene(Mat4x4& ViewProjMatrix, Vec3& EyePosition, const std::vector<Ref<PointLight>>& PointLights);

		static void EndScene(const Ref<Context>& RenderingContext);

		static void Submit(Mat4x4& ModelMatrix, const Ref<Mesh>& ObjectMesh, const Ref<Material>& ObjectMaterial, bool AllowDiscrimination = true);

		static void Init(const Ref<RenderingAPI>& API);

	private:		
		
		struct Submission
		{
			bool AllowDiscrimination = false;
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

		static void Discriminate(std::vector<Submission>& Submissions);

		static void Sort(std::vector<Submission>& Submissions);

		static inline bool _InScene = false;
	
		static inline Ref<RenderingAPI> _API;
	};
}

