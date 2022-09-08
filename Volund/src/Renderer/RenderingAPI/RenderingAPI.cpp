#include "PCH/PCH.h"
#include "RenderingAPI.h"

#include "OpenGLRenderingAPI.h"

namespace Volund
{
	RenderingAPI::API RenderingAPI::_SelectedAPI = API::NONE;

	std::unordered_map<std::string, RenderingAPI::API> RenderingAPI::_APINames =
	{
		{VOLUND_GRAPHICSAPI_NONE, API::NONE},
		{VOLUND_GRAPHICSAPI_OPENGL, API::OPENGL}
	};

	RenderingAPI::API RenderingAPI::GetSelectedAPI()
	{
		if (_SelectedAPI == API::NONE)
		{
			JSON ConfigJSON = JSON::Load(VOLUND_CONFIG_JSON);

			std::string NewAPI = ConfigJSON["Renderer"]["API"];

			if (_APINames.contains(NewAPI))
			{
				_SelectedAPI = _APINames[NewAPI];
			}
			else
			{
				VOLUND_ERROR("Unknown GraphicsAPI specified (%s)!", NewAPI.c_str());
			}
		}

		return _SelectedAPI;
	}

	Ref<RenderingAPI> RenderingAPI::Create()
	{
		switch (GetSelectedAPI())
		{
		case API::OPENGL:
			{
				return std::make_shared<OpenGLRenderingAPI>();
			}
			break;
		default:
			{
				VOLUND_ERROR("Creating a RenderingAPI without a specified API!");
				return nullptr;
			}
			break;
		}
	}
}
