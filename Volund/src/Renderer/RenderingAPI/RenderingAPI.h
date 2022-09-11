#pragma once

#include "Renderer/Mesh/Mesh.h"

namespace Volund
{
	class RenderingAPI
	{
	public:
		enum API
		{
			NONE,
			OPENGL
		};

		virtual void SetViewPort(int32_t X, int32_t Y, int32_t Width, int32_t Height) = 0;

		virtual void SetClearColor(const RGBA& Color) = 0;

		virtual void Clear() = 0;

		virtual void DrawIndexed(const Ref<Mesh>& VArray) = 0;

		virtual void Init() = 0;

		static API GetSelectedAPI();

		static Ref<RenderingAPI> Create(API SelectedAPI);

	private:

		static inline API _SelectedAPI;
	};
}
