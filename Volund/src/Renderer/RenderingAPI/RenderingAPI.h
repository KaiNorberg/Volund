#pragma once

#define VOLUND_GRAPHICSAPI_NONE "None"
#define VOLUND_GRAPHICSAPI_OPENGL "OpenGL"

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

		virtual void Clear(RGBA const& Color) = 0;

		static void LoadJSONSettings();

		static API GetAPI();

	private:

		static std::unordered_map<std::string, API> _APINames;
		static API _SelectedAPI;
	};
}

