#pragma once

namespace Volund
{
	class Window;

	class RenderingContext
	{
	public:

		virtual void MakeCurrent() = 0;

		virtual void SetVSync(bool Enabled) = 0;

		static Ref<RenderingContext> Create(void* DeviceContext);

		virtual ~RenderingContext() = default;

	protected:
	};
}
