#pragma once

#define TEXTINPUTDIALOG_LENGTH 124

class TextInputDialog
{
public:

	static void Start(std::function<void(void)> Catch, const std::string& Message);

	static std::string GetText();

	static bool Draw();

private:

	static inline bool _ShouldDraw = false;

	static inline std::string _Text;

	static inline std::string _Message;

	static inline std::function<void(void)> _Catch;
};

