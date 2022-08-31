#pragma once

#define VOLUND_GRAPHICSAPI_NONE "None"
#define VOLUND_GRAPHICSAPI_OPENGL "OpenGL"

#include "Renderer/VertexArray/VertexArray.h"
#include "Scene/Scene.h"
#include "RenderingAPI/RenderingAPI.h"
#include "Context/Context.h"

#include "Component/Camera/Camera.h"

#include "Renderer/Shader/Shader.h"

namespace Volund
{
	class Renderer
	{
	public:

		static void BeginScene(Camera* Cam);
		static void EndScene();

		static void Submit(Mat4x4& ModelMatrix, Ref<VertexArray> const& VArray, Ref<Shader> const& shader);

		Renderer(Ref<Window>& window);

		~Renderer();

	private:		
		
		static struct SceneData
		{
			Mat4x4 ViewProjMatrix;
		} _SceneData;

		static Ref<RenderingAPI> _RenderingAPI;
		static Ref<Context> _Context;
	};
}

