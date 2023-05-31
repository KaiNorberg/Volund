#pragma once

#include "../ImGuiObject.h"

namespace Volund
{	
	class ImGuiSeparator : public ImGuiObject
	{
	public:

		void Procedure(const Event& e) override;

	private:

		std::string m_Text;
	};
}

