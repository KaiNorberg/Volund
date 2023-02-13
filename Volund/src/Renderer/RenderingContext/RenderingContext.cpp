#include "PCH/PCH.h"
#include "RenderingContext.h"

#include "OpenGLContext.h"

#include "Renderer/RenderingAPI/RenderingAPI.h"

namespace Volund
{
	Ref<RenderingContext> RenderingContext::Create(void* DeviceContext)
	{
		switch (RenderingAPI::GetSelectedAPI())
		{
		case GraphicsAPI::OPENGL:
		{
			return std::make_shared<OpenGLContext>(DeviceContext);
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
