#include "PCH/PCH.h"
#include "RenderingAPI.h"

#include "OpenGLRenderingAPI.h"

#include "VML/VML.h"

namespace Volund
{
	RenderingAPI::API RenderingAPI::GetSelectedAPI()
	{
		return _SelectedAPI;
	}

	Ref<RenderingAPI> RenderingAPI::Create(API SelectedAPI)
	{
		if (SelectedAPI != API::NONE || SelectedAPI == _SelectedAPI)
		{
			_SelectedAPI = SelectedAPI;
		}
		else
		{
			VOLUND_ERROR("Unable to create a RenderingAPI more then once!");
		}

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
