#include "PCH/PCH.h"
#include "RenderingAPI.h"

namespace Volund
{
	RenderingAPI::API RenderingAPI::_SelectedAPI = API::NONE;

	std::unordered_map<std::string, RenderingAPI::API> RenderingAPI::_APINames =
	{
		{VOLUND_GRAPHICSAPI_NONE, API::NONE},
		{VOLUND_GRAPHICSAPI_OPENGL, API::OPENGL}
	};

	void RenderingAPI::LoadJSONSettings()
	{
		JSON ConfigFile = JSON::Load(VOLUND_CONFIG_JSON);

		std::string API = ConfigFile["Renderer"]["GraphicsAPI"];

		if (_APINames.contains(API))
		{
			_SelectedAPI = _APINames[API];
		}
		else
		{
			VOLUND_ERROR("Unknown GraphicsAPI specified (%s)!", API.c_str());
		}
	}

	RenderingAPI::API RenderingAPI::GetAPI()
	{
		return _SelectedAPI;
	}
}