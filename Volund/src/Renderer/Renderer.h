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
	class Renderer
	{
	public:

		static void BeginScene(Mat4x4& ViewProjMatrix, Vec3& EyePosition);	

		static void EndScene();

		static void SubmitPointLight(const RGB& Color, float Brightness, const Vec3& Position);

		static void SubmitObject(Mat4x4& ModelMatrix, const Ref<Mesh>& ObjectMesh, const Ref<Material>& ObjectMaterial, bool AllowDiscrimination = true);

		static void Init(const Ref<RenderingAPI>& API);

	private:		
		
		struct PointLight
		{
			RGB Color;
			float Brightness;
			Vec3 Position;
		};

		struct Object
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
			std::vector<PointLight> PointLights;
			std::vector<Object> Objects;

		} _SceneData;

		static void Discriminate(std::vector<Object>& Submissions);

		static void Sort(std::vector<Object>& Submissions);

		static inline bool _InScene = false;
	
		static inline Ref<RenderingAPI> _API;
	};
}

