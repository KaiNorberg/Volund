#pragma once

namespace Volund
{
	class Window;

	class Context
	{
	public:

		virtual void Flush() = 0;

		static Context* Create(Ref<Window>& window);

		virtual ~Context() = default;

	private:
	};
}


