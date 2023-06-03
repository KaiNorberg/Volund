#pragma once

#include "Rendering/Mesh/Mesh.h"
#include "Rendering/Framebuffer/Framebuffer.h"

namespace Volund
{
	enum class GraphicsAPI
	{
		None,
		OpenGL
	};

	class RenderingAPIInstance
	{
	public:

		virtual IVec2 GetViewSize() = 0;

		virtual void Clear(const RGBA color) = 0;

		virtual void SetViewPort(int32_t x, int32_t y, int32_t width, int32_t height) = 0;

		virtual void DrawIndexed(const Ref<Mesh>& mesh) = 0;

		virtual void BlitFramebuffer(Ref<Framebuffer> readBuffer, Ref<Framebuffer> drawBuffer) = 0;

		virtual ~RenderingAPIInstance() = default;
	};

	class RenderingAPI
	{
	public:

		static IVec2 GetViewSize();

		static void Clear(const RGBA color = RGBA(0.0f, 0.0f, 0.0f, 1.0f));

		static void SetViewPort(int32_t x, int32_t y, int32_t width, int32_t height);

		static void DrawIndexed(const Ref<Mesh>& mesh);
		
		static void BlitFramebuffer(Ref<Framebuffer> readBuffer, Ref<Framebuffer> drawBuffer);

		static void Init(GraphicsAPI api);

		static GraphicsAPI GetSelectedAPI();

	private:

		RenderingAPI() = delete;

		static inline Ref<RenderingAPIInstance> m_Instance;

		static inline GraphicsAPI m_SelectedAPI;
	};
}
