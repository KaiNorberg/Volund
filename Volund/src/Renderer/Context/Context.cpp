#include "PCH/PCH.h"
#include "Context.h"

#include "OpenGLContext.h"

#include "Time/Time.h"
#include "Renderer/RenderingAPI/RenderingAPI.h"

namespace Volund
{
	Ref<Context> Context::Create(Ref<Window> const& window)
	{		
		switch (RenderingAPI::GetSelectedAPI())
		{
		case RenderingAPI::API::OPENGL:
		{
			return Ref<Context>(new OpenGLContext(window));
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