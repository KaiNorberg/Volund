#pragma once

#define VOLUND_GRAPHICSAPI_NONE "None"
#define VOLUND_GRAPHICSAPI_OPENGL "OpenGL"

#include "Renderer/Mesh/Mesh.h"
#include "Scene/Scene.h"
#include "RenderingAPI/RenderingAPI.h"
#include "Context/Context.h"
#include "Renderer/Shader/Shader.h"
#include "Renderer/Material/Material.h"

namespace Volund
{
	class Renderer
	{
	public:

		static void BeginScene(Mat4x4& ViewProjMatrix);
		static void EndScene();

		static void Submit(Mat4x4& ModelMatrix, Ref<Mesh> const& ObjectMesh, Ref<Material> const& ObjectMaterial);

		Renderer(Ref<Window>& window);

		~Renderer();

	private:		
		
		struct Submission
		{
			Mat4x4 ModelMatrix;
			Ref<Mesh> ObjectMesh;
			Ref<Material> ObjectMaterial;
		};

		static struct SceneData
		{
			Mat4x4 ViewProjMatrix;
			std::vector<Submission> Submissions;
		} _SceneData;

		static Ref<RenderingAPI> _RenderingAPI;
		static Ref<Context> _Context;
	};
}

