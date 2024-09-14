#include "PCH/PCH.h"
#include "RenderingAPI.h"

#include "OpenGLRenderingAPI.h"

namespace Volund
{
	IVec2 RenderingAPI::GetViewSize()
	{
		return m_Instance->GetViewSize();
	}

	void RenderingAPI::Clear(const RGBA color)
	{
		VOLUND_PROFILE_FUNCTION();

		m_Instance->Clear(color);
	}

	void RenderingAPI::SetViewPort(const int32_t x, const int32_t y, const int32_t width, const int32_t height)
	{
		VOLUND_PROFILE_FUNCTION();

		m_Instance->SetViewPort(x, y, width, height);
	}

	void RenderingAPI::DrawIndexed(uint64_t indexCount)
	{
		VOLUND_PROFILE_FUNCTION();

		m_Instance->DrawIndexed(indexCount);
	}

	void RenderingAPI::Draw(uint64_t first, uint64_t count)
	{
		m_Instance->Draw(first, count);
	}

	void RenderingAPI::BlitFramebuffer(std::shared_ptr<Framebuffer> readBuffer, std::shared_ptr<Framebuffer> drawBuffer)
	{
		VOLUND_PROFILE_FUNCTION();

		m_Instance->BlitFramebuffer(readBuffer, drawBuffer);
	}

	void RenderingAPI::Init(GraphicsAPI api)
	{
		if (m_Instance != nullptr)
		{
			VOLUND_ERROR("The RenderingAPI is already initialized!");
		}

		m_SelectedAPI = api;

		switch (api)
		{
		case GraphicsAPI::OpenGL:
		{
			m_Instance = std::make_shared<OpenGLRenderingAPI>();
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
		return m_SelectedAPI;
	}
}
