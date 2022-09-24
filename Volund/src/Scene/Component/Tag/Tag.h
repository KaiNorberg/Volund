#pragma once

#include "Scene/Component/Component.h"

namespace Volund
{
	class Tag : public Component
	{
	public:

		std::string String = "";

		VML Serialize() override;

		Tag() = default;

		Tag(std::string String);

	private:
	};
}