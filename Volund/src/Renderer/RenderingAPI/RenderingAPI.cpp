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

	RenderingAPI::API RenderingAPI::GetAPI()
	{
		return _SelectedAPI;
	}

	Ref<RenderingAPI> RenderingAPI::Create()
	{
		if (RenderingAPI::GetAPI() == API::NONE)
		{
			JSON ConfigFile = JSON::Load(VOLUND_CONFIG_JSON);

			std::string API = ConfigFile["Renderer"]["API"];

			if (_APINames.contains(API))
			{
				_SelectedAPI = _APINames[API];
			}
			else
			{
				VOLUND_ERROR("Unknown GraphicsAPI specified (%s)!", API.c_str());
			}
		}

		switch (RenderingAPI::GetAPI())
		{
		case RenderingAPI::API::OPENGL:
		{
			return Ref<RenderingAPI>(new OpenGLRenderingAPI());
		}
		break;
		default:
		{
			VOLUND_ERROR("Creating a Contex without a specified GraphicsAPI!");
			return nullptr;
		}
		break;
		}
	}
}