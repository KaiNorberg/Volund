#pragma once

#include "PCH/PCH.h"
#include "Logger.h"

#ifdef VOLUND_DIST
#include <Windows.h>
#endif

namespace Volund
{
	Logger Logger::_CoreLogger = Logger("VOLUND");
	Logger Logger::_ClientLogger = Logger("CLIENT");

	Logger& Logger::GetCoreLogger()
	{
		return _CoreLogger;
	}

	Logger& Logger::GetClientLogger()
	{
		return _ClientLogger;
	}

	void Logger::Info(const char* Format, ...) const
	{
		std::va_list Args;
		va_start(Args, Format);

		printf("\033[0;31m[%s]\033[0;32m %s: ", std::format("{:%H:%M:%OS}", std::chrono::system_clock::now()).c_str(),
		       this->_Name.c_str());
		vprintf(Format, Args);
		printf("\n");

		va_end(Args);
	}

	void Logger::Warning(const char* Format, ...) const
	{
		std::va_list Args;
		va_start(Args, Format);

		printf("\033[0;31m[%s]\033[0;33m %s: ", std::format("{:%H:%M:%OS}", std::chrono::system_clock::now()).c_str(),
		       this->_Name.c_str());
		vprintf(Format, Args);
		printf("\n");

		#ifdef VOLUND_DIST
		std::string FormatedString = FormatString(Format, Args);
		MessageBox(NULL, std::wstring(FormatedString.begin(), FormatedString.end()).c_str(), L"WARNING!", MB_ICONWARNING | MB_OK);
		#endif

		va_end(Args);
	}

	void Logger::Error(const char* Format, ...) const
	{
		std::va_list Args;
		va_start(Args, Format);

		printf("\033[0;31m[%s] %s: ", std::format("{:%H:%M:%OS}", std::chrono::system_clock::now()).c_str(),
		       this->_Name.c_str());
		vprintf(Format, Args);
		printf("\n");

		va_end(Args);

		#ifdef VOLUND_DIST
		std::string FormatedString = FormatString(Format, Args);
		MessageBox(NULL, std::wstring(FormatedString.begin(), FormatedString.end()).c_str(), L"ERROR!", MB_ICONERROR | MB_OK);
		#endif

		abort();
	}

	Logger::Logger(std::string_view Name)
	{
		this->_Name = Name;
	}

	std::string Logger::FormatString(const char* Format, ...)
	{
		std::va_list Args;
		va_start(Args, Format);

		size_t Size = std::vsnprintf(nullptr, 0, Format, Args) + 1;

		std::string FormatedString;
		FormatedString.resize(Size);
		std::vsnprintf(FormatedString.data(), Size, Format, Args);

		va_end(Args);

		return FormatedString;
	}
} //namespace Volund
