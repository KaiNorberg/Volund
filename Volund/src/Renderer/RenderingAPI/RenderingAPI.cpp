#include "PCH/PCH.h"
#include "RenderingAPI.h"

#include "OpenGLRenderingAPI.h"

namespace Volund
{
	IVec2 RenderingAPI::GetViewSize()
	{
		return _Instance->GetViewSize();
	}

	void RenderingAPI::Clear(const RGBA Color)
	{
		VOLUND_PROFILE_FUNCTION();

		_Instance->Clear(Color);
	}
	
	void RenderingAPI::SetViewPort(int32_t X, int32_t Y, int32_t Width, int32_t Height)
	{
		VOLUND_PROFILE_FUNCTION();

		_Instance->SetViewPort(X, Y, Width, Height);
	}

	void RenderingAPI::DrawIndexed(const Ref<Mesh>& VArray)
	{
		VOLUND_PROFILE_FUNCTION();

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
