#pragma once

#include "../ImGuiObject.h"

namespace Volund
{	
	class ImGuiSeparator : public ImGuiObject
	{
	public:

		void Procedure(const Event& e) override;

		ImGuiSeparator(const std::string& id);

	private:

		std::string m_Text;
	};
}

