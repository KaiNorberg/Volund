#include "Rendering/RenderingAPI.h"

#include "Rendering/OpenGL/OpenGLRenderingAPI.h"

#include "Instrumentor.h"

namespace Volund
{
	IVec2 RenderingAPI::GetViewSize()
	{
		return m_instance->GetViewSize();
	}

	void RenderingAPI::Clear(const RGBA color)
	{
		VOLUND_PROFILE_FUNCTION();

		m_instance->Clear(color);
	}

	void RenderingAPI::SetViewPort(const int32_t x, const int32_t y, const int32_t width, const int32_t height)
	{
		VOLUND_PROFILE_FUNCTION();

		m_instance->SetViewPort(x, y, width, height);
	}

	void RenderingAPI::DrawIndexed(uint64_t indexCount)
	{
		VOLUND_PROFILE_FUNCTION();

		m_instance->DrawIndexed(indexCount);
	}

	void RenderingAPI::Draw(uint64_t first, uint64_t count)
	{
		m_instance->Draw(first, count);
	}

	void RenderingAPI::BlitFramebuffer(std::shared_ptr<Framebuffer> readBuffer, std::shared_ptr<Framebuffer> drawBuffer)
	{
		VOLUND_PROFILE_FUNCTION();

		m_instance->BlitFramebuffer(readBuffer, drawBuffer);
	}

	void RenderingAPI::Init(GraphicsAPI api)
	{
		if (m_instance != nullptr)
		{
			VOLUND_ERROR("The RenderingAPI is already initialized!");
		}

		m_selectedAPI = api;

		switch (api)
		{
		case GraphicsAPI::OpenGL:
		{
			m_instance = std::make_shared<OpenGLRenderingAPI>();
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
		return m_selectedAPI;
	}
}