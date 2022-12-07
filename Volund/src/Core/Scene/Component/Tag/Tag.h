#pragma once

#include "Core/Scene/Component/Component.h"

namespace Volund
{
	class Tag : public Component
	{
	public:

		std::string String = "";

		Tag() = default;

		Tag(std::string String);

	private:
	};
}