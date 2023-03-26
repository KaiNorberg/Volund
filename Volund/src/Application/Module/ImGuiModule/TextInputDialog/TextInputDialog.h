#pragma once

#define TEXTINPUTDIALOG_LENGTH 124

namespace Volund
{
	class TextInputDialog
	{
	public:

		static void Start(std::function<void(void)> Catch, const std::string& message);

		static std::string GetText();

		static bool Draw();

	private:

		static inline bool m_ShouldDraw = false;

		static inline std::string m_Text;

		static inline std::string m_Message;

		static inline std::function<void(void)> m_Catch;
	};
}