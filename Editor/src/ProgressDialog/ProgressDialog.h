#pragma once

class ProgressDialog
{
public:

	static void SetMessage(const std::string& Text);

	static void Start(std::function<void(void)> Catch, const std::string& Text);

	static bool Update();

private:

	static bool IsReady();

	static bool Spinner(const char* label, float radius, int thickness, const uint32_t& color);

	static inline bool _ShouldDraw = false;

	static inline std::future<void> _CatchFuture;

	static inline std::string _CatchMessage;
};

