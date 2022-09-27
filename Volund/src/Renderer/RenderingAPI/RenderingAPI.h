#pragma once

#include "Renderer/Mesh/Mesh.h"

namespace Volund
{
	enum class GraphicsAPI
	{
		NONE,
		OPENGL
	};

	class RenderingAPIInstance
	{
	public:

		virtual void Clear() = 0;

		virtual void SetClearColor(const RGBA& Color) = 0;

		virtual void SetViewPort(int32_t X, int32_t Y, int32_t Width, int32_t Height) = 0;

		virtual void DrawIndexed(const Ref<Mesh>& VArray) = 0;

		virtual ~RenderingAPIInstance() = default;
	};

	class RenderingAPI
	{
	public:

		static void Clear();

		static void SetClearColor(const RGBA& Color);

		static void SetViewPort(int32_t X, int32_t Y, int32_t Width, int32_t Height);

		static void DrawIndexed(const Ref<Mesh>& VArray);

		static void Select(GraphicsAPI API);
			
		static void Init();

		static GraphicsAPI GetSelectedAPI();

	private:

		static inline Ref<RenderingAPIInstance> _Instance;

		static inline GraphicsAPI _SelectedAPI;
	};
}
