#include "PCH/PCH.h"
#include "Renderer.h"

namespace Volund
{
	GraphicsAPI Renderer::_SelectedAPI = GraphicsAPI::NONE;

	std::unordered_map<std::string, GraphicsAPI> Renderer::GraphicsAPINames =
	{
		{VOLUND_GRAPHICSAPI_NONE, GraphicsAPI::NONE},
		{VOLUND_GRAPHICSAPI_OPENGL, GraphicsAPI::OPENGL}
	};

	void Renderer::LoadJSONSettings()
	{
		JSON ConfigFile = JSON::Load(CONFIG_JSON);

		std::string API = ConfigFile["Renderer"]["GraphicsAPI"];

		if (GraphicsAPINames.contains(API))
		{
			_SelectedAPI = GraphicsAPINames[API];
		}
		else
		{
			VOLUND_ERROR("Unknown GraphicsAPI specified (%s)!", API.c_str());
		}
	}

	GraphicsAPI Renderer::GetGraphicsAPI()
	{
		return _SelectedAPI;
	}
}