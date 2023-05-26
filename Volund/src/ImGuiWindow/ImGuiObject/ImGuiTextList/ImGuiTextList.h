#pragma once

#include "../ImGuiObject.h"

namespace Volund
{
	/// <summary>
	/// Souports terminal style color codes.
	/// </summary>
	class ImGuiTextList : public ImGuiObject
	{
	public:

		uint64_t GetSize();

		void PushText(const std::string& text);

		void SetText(uint32_t i, const std::string& text);

		std::string GetText(uint32_t i);

		void Procedure(const Event& e) override;

		ImGuiTextList(const std::string& id);

	private:

		float m_TotalTime = 0.0f;

		std::vector<std::string> m_TextList;
	};
}

