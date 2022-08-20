#pragma once

namespace Volund
{
	class SimpleComponent
	{
	public:

		virtual void Start();

		virtual void Update();

		virtual const std::string Type();

	private:

	};
}

