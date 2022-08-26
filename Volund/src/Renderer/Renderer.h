#pragma once

#define VOLUND_GRAPHICSAPI_NONE "None"
#define VOLUND_GRAPHICSAPI_OPENGL "OpenGL"

namespace Volund
{
	enum class GraphicsAPI
	{
		NONE,
		OPENGL
	};

	class Renderer
	{
	public:

		static void LoadJSONSettings();

		static GraphicsAPI GetGraphicsAPI();

	private:

		static std::unordered_map<std::string, GraphicsAPI> GraphicsAPINames;
		static GraphicsAPI _SelectedAPI;
	};
}

