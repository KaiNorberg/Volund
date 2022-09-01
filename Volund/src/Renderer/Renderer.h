#pragma once

#define VOLUND_GRAPHICSAPI_NONE "None"
#define VOLUND_GRAPHICSAPI_OPENGL "OpenGL"

#include "Renderer/Mesh/Mesh.h"
#include "Scene/Scene.h"
#include "RenderingAPI/RenderingAPI.h"
#include "Context/Context.h"
#include "Renderer/Shader/Shader.h"

namespace Volund
{
	class Renderer
	{
	public:

		static void BeginScene(Mat4x4& ViewProjMatrix);
		static void EndScene();

		static void Submit(Mat4x4 ModelMatrix, Ref<Mesh> const& ObjectMesh, Ref<Shader> const& ObjectShader);

		Renderer(Ref<Window>& window);

		~Renderer();

	private:		
		
		struct EntityData
		{
			Mat4x4 ModelMatrix;
			Ref<Mesh> ObjectMesh;
			Ref<Shader> ObjectShader;
		};

		static struct SceneData
		{
			Mat4x4 ViewProjMatrix;
			std::vector<EntityData> Submissions;
		} _SceneData;

		static Ref<RenderingAPI> _RenderingAPI;
		static Ref<Context> _Context;
	};
}

