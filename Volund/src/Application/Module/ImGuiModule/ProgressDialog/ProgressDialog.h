#pragma once

namespace Volund
{
	class ProgressDialog
	{
	public:

		static void SetMessage(const std::string& text);

		static void Start(std::function<void(void)> Catch, const std::string& text);

		static bool Draw();

	private:

		static bool IsReady();

		static bool Spinner(const char* label, float radius, int thickness, const uint32_t& color);

		static inline bool m_ShouldDraw = false;

		static inline std::future<void> m_CatchFuture;

		static inline std::string m_CatchMessage;
	};
}
