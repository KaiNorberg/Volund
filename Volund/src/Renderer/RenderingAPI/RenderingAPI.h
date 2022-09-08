#pragma once

#define VOLUND_GRAPHICSAPI_NONE "None"
#define VOLUND_GRAPHICSAPI_OPENGL "OpenGL"

#include "Renderer/Mesh/Mesh.h"

namespace Volund
{
	class RenderingAPI
	{
	public:
		enum class API
		{
			NONE,
			OPENGL
		};

		virtual void SetViewPort(int32_t X, int32_t Y, int32_t Width, int32_t Height) = 0;

		virtual void SetClearColor(const RGBA& Color) = 0;

		virtual void Clear() = 0;

		virtual void DrawIndexed(const Ref<Mesh>& VArray) = 0;

		static API GetSelectedAPI();

		static Ref<RenderingAPI> Create();

	private:
		static std::unordered_map<std::string, API> _APINames;
		static API _SelectedAPI;
	};
}
