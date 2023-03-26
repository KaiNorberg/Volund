#pragma once

#include "Renderer/Mesh/Mesh.h"

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

		virtual ~RenderingAPIInstance() = default;
	};

	class RenderingAPI
	{
	public:

		static IVec2 GetViewSize();

		static void Clear(const RGBA color = RGBA(0.0f, 0.0f, 0.0f, 1.0f));

		static void SetViewPort(int32_t x, int32_t y, int32_t width, int32_t height);

		static void DrawIndexed(const Ref<Mesh>& mesh);

		static void Select(GraphicsAPI api);
			
		static void Init();

		static GraphicsAPI GetSelectedAPI();

	private:

		static inline Ref<RenderingAPIInstance> m_Instance;

		static inline GraphicsAPI m_SelectedApi;
	};
}
