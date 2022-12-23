#pragma once

namespace Volund
{
	class Window;

	class Context
	{
	public:

		virtual void MakeCurrent() = 0;

		virtual void SetVSync(bool Enabled) = 0;

		static Ref<Context> Create(void* DeviceContext);

		virtual ~Context() = default;

	protected:
	};
}
