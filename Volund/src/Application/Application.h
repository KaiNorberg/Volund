#pragma once

#include "Layer/Layer.h"

namespace Volund
{
	class Application
	{
	public:
		void Run();

		void AttachLayer(Layer* L);

		void Terminate();

		bool ShouldRun() const;

		Application();

		virtual ~Application();

	protected:
		bool _ShouldRun = true;

	private:
		void Loop() const;

		std::vector<Ref<Layer>> _LayerStack;
	};
}
