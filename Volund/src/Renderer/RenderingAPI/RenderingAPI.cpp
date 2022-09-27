#include "PCH/PCH.h"
#include "RenderingAPI.h"

#include "OpenGLRenderingAPI.h"

#include "VML/VML.h"

namespace Volund
{
	void RenderingAPI::Clear()
	{
		_Instance->Clear();
	}

	void RenderingAPI::SetClearColor(const RGBA& Color)
	{
		_Instance->SetClearColor(Color);
	}
	
	void RenderingAPI::SetViewPort(int32_t X, int32_t Y, int32_t Width, int32_t Height)
	{
		_Instance->SetViewPort(X, Y, Width, Height);
	}

	void RenderingAPI::DrawIndexed(const Ref<Mesh>& VArray)
	{
		_Instance->DrawIndexed(VArray);
	}

	void RenderingAPI::Select(GraphicsAPI API)
	{
		_SelectedAPI = API;
	}

	void RenderingAPI::Init()
	{
		switch (RenderingAPI::GetSelectedAPI())
		{
		case GraphicsAPI::OPENGL:
		{
			_Instance = std::make_shared<OpenGLRenderingAPI>();
		}
		break;
		default:
		{
			VOLUND_ERROR("Initializing the RenderingAPI without a specified GraphicsAPI!");
		}
		break;
		}
	}

	GraphicsAPI RenderingAPI::GetSelectedAPI()
	{
		return _SelectedAPI;
	}
}
