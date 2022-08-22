#pragma once

namespace Volund
{
	class SimpleComponent
	{
	public:

		virtual void OnInit() {};

		virtual void OnRemove() {};

		virtual void OnUpdate() {};

		virtual const std::string Type() { return "SimpleComponent"; }

	private:

	};
}

