#pragma once

#include "../ImGuiObject.h"

namespace Volund
{
	class ImGuiText : public ImGuiObject
	{
	public:

		void Procedure(const Event& e) override;

		ImGuiText(const std::string& id);

	private:
	};
}

