#pragma once

#include "../ImGuiObject.h"

namespace Volund
{
	class ImGuiButton : public ImGuiObject
	{
	public:

		float Alignment = 0.0f;

		void SetText(const std::string& text);

		std::string GetText();

		void SetCallback(std::function<void(ImGuiButton*)> callback);

		std::function<void(ImGuiButton*)> GetCallback();

		void Procedure(const Event& e) override;

		ImGuiButton(const std::string& text, std::function<void(ImGuiButton*)> callback, float alignment = 0.0f);

	private:

		std::function<void(ImGuiButton*)> m_Callback;

		std::string m_Text;
	};
}