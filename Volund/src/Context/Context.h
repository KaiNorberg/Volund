#pragma once

namespace Volund
{
	class Window;

	class Context
	{
	public:

		static Context* Create(Window* window);

		virtual void Flush() = 0;

	private:
	};
}


