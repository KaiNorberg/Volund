#pragma once

namespace Volund
{
	class Layer
	{
	public:
		virtual void OnAttach() {};

		virtual void OnDetach() {};

		virtual void OnUpdate() {};
	
		virtual ~Layer() {}
	};
}