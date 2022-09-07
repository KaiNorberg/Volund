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
		return _SelectedAPI;
	}

	void RenderingAPI::SelectAPI(std::string const& NewAPI)
	{
		if (_APINames.contains(NewAPI))
		{
			SelectAPI(_APINames[NewAPI]);
		}
		else
		{
			VOLUND_ERROR("Unknown GraphicsAPI specified (%s)!", NewAPI.c_str());
		}
	}

	void RenderingAPI::SelectAPI(RenderingAPI::API NewAPI)
	{
		if (_SelectedAPI == API::NONE)
		{
			_SelectedAPI = NewAPI;
		}
		else
		{
			VOLUND_ERROR("An API has already been selected!");
		}
	}

	Ref<RenderingAPI> RenderingAPI::Create()
	{
		switch (RenderingAPI::GetSelectedAPI())
		{
		case RenderingAPI::API::OPENGL:
		{
			return Ref<RenderingAPI>(new OpenGLRenderingAPI());
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