#pragma once

namespace Volund
{
	class Window;

	class RenderingContext
	{
	public:

		virtual void MakeCurrent() = 0;

		virtual void SetVSync(bool enabled) = 0;

		static Ref<RenderingContext> Create(void* deviceContext);

		virtual ~RenderingContext() = default;

	protected:
	};
}
