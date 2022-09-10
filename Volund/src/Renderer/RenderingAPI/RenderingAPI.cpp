#include "PCH/PCH.h"
#include "RenderingAPI.h"

#include "OpenGLRenderingAPI.h"

#include "VML/VML.h"

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
			VML Config(VOLUND_CONFIG);

			for (auto& [EntityName, EntityVML] : Config["Renderer"])
			{
				VOLUND_INFO(EntityName.c_str());
			}

			std::string NewAPI = Config["Renderer"].Get("API");

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
