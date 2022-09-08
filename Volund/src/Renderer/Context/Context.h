#pragma once

namespace Volund
{
	class Window;

	class Context
	{
	public:
		virtual void MakeCurrent() = 0;

		virtual void SetVSync(bool Enabled) = 0;

		virtual void Flush() = 0;

		Ref<Window> GetWindow();

		static Ref<Context> Create(const Ref<Window>& TargetWindow);

		virtual ~Context() = default;

	protected:
		Ref<Window> _Window;
	};
}
