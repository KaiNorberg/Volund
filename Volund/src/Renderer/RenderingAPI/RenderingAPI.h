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

		virtual void SetClearColor(RGBA const& Color) = 0;

		virtual void Clear() = 0;

		virtual void DrawIndexed(Ref<Mesh> const& VArray) = 0;

		static API GetAPI();

		static Ref<RenderingAPI> Create();

	private:

		static std::unordered_map<std::string, API> _APINames;
		static API _SelectedAPI;
	};
}

