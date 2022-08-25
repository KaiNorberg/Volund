#include "PCH/PCH.h"
#include "Context.h"

#include "OpenGLContext.h"

namespace Volund
{
	Context* Context::Create(Window* window)
	{
		JSON ConfigFile = JSON::Load(CONFIG_JSON);
		
		if (ConfigFile["Misc"]["GraphicsAPI"] == "OpenGL")
		{
			return new OpenGLContext(window);
		}
		else
		{
			VOLUND_CORE_ERROR("Unknown GraphicsAPI (%s)", ConfigFile["Misc"]["GraphicsAPI"].GetAs<std::string>().c_str());
			return nullptr;
		}
	}
}