#include "PCH/PCH.h"
#include "Context.h"

#include "OpenGLContext.h"

#include "Time/Time.h"
#include "Renderer/Renderer.h"

namespace Volund
{
	Context* Context::Create(Window* window)
	{		
		switch (Renderer::GetGraphicsAPI())
		{
		case GraphicsAPI::OPENGL:
		{
			return new OpenGLContext(window);
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