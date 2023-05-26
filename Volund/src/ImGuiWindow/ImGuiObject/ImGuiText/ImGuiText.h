#pragma once

#include "../ImGuiObject.h"

namespace Volund
{	
	/// <summary>
	/// Souports terminal style color codes.
	/// </summary>
	class ImGuiText : public ImGuiObject
	{
	public:

		void SetText(const std::string& text);

		std::string GetText();

		void Procedure(const Event& e) override;

		ImGuiText(const std::string& id, const std::string& text);

	private:

		std::string m_Text;
	};
}

