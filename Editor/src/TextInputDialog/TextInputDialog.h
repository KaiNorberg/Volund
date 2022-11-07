#pragma once

class TextInputDialog
{
public:

	static void Start(std::function<void(const std::string&)> Catch, const std::string& Message);

	static bool Update();

private:

	static inline bool _ShouldDraw = false;

	static inline std::string _Message;

	static inline std::function<void(const std::string&)> _Catch;
};

