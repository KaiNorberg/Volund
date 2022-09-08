#pragma once

#include "Renderer/RenderingAPI/RenderingAPI.h"

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

		static Ref<Context> Create(Ref<Window> const& TargetWindow);

		virtual ~Context() = default;

	protected:		

		Ref<Window> _Window;
	};
}


