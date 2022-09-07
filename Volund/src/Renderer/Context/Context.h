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

		static Ref<Context> Create(Ref<Window> const& window);

		virtual ~Context() = default;

	private:
	};
}


