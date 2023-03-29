#pragma once

namespace Volund
{
	class Dialog
	{
	public:

		static std::string OpenFolder();

		static std::string OpenFile();

		static void Message(const std::string& title, const std::string& message, const std::string& dialogType, const std::string& iconType);

	private:
	};
}