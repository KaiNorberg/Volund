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

		std::string FormatedString = this->FormatString(LoggerColor::GREEN, Format, Args);
		if (this->_Callback != nullptr)
		{
			this->_Callback(FormatedString);
		}
		std::cout << FormatedString << '\n';

		va_end(Args);
	}

	void Logger::Warning(const char* Format, ...) const
	{
		std::va_list Args;
		va_start(Args, Format);

		std::string FormatedString = this->FormatString(LoggerColor::YELLOW, Format, Args);
		if (this->_Callback != nullptr)
		{
			this->_Callback(FormatedString);
		}
		#ifdef VOLUND_DIST		
		std::string FormatedString = this->FormatString(Format, Args);
		MessageBox(NULL, std::wstring(FormatedString.begin(), FormatedString.end()).c_str(), L"WARNING!", MB_ICONWARNING | MB_OK);
		#else		
		std::cout << FormatedString << '\n';
		#endif

		va_end(Args);
	}

	void Logger::Error(const char* Format, ...) const
	{
		std::va_list Args;
		va_start(Args, Format);

		std::string FormatedString = this->FormatString(LoggerColor::RED, Format, Args);
		if (this->_Callback != nullptr)
		{
			this->_Callback(FormatedString);
		}
		#ifdef VOLUND_DIST		
		std::string FormatedString = this->FormatString(Format, Args);
		MessageBox(NULL, std::wstring(FormatedString.begin(), FormatedString.end()).c_str(), L"ERROR!", MB_ICONERROR | MB_OK);
		#else		
		std::cout << FormatedString << '\n';
		#endif

		va_end(Args);

		abort();
	}

	void Logger::SetCallback(LoggerCallback NewCallback)
	{
		this->_Callback = NewCallback;
	}

	Logger::Logger(std::string_view Name)
	{
		this->_Name = Name;
		this->_Callback = nullptr;
	}

	std::string Logger::FormatString(LoggerColor Color, const char* Format, std::va_list Args) const
	{
		std::string Output = VOLUND_LOGGERCOLOR_RED;
		Output += std::format("{:%H:%M:%OS}", std::chrono::system_clock::now()) + " " + this->_Name + VOLUND_LOGGERCOLOR_WHITE + " - ";

		switch (Color)
		{
		case LoggerColor::BLACK:
		{
			Output += VOLUND_LOGGERCOLOR_BLACK;
		}
		break;
		case LoggerColor::RED:
		{
			Output += VOLUND_LOGGERCOLOR_RED;
		}
		break;
		case LoggerColor::GREEN:
		{
			Output += VOLUND_LOGGERCOLOR_GREEN;
		}
		break;
		case LoggerColor::YELLOW:
		{
			Output += VOLUND_LOGGERCOLOR_YELLOW;
		}
		break;
		case LoggerColor::BLUE:
		{
			Output += VOLUND_LOGGERCOLOR_BLUE;
		}
		break;
		case LoggerColor::MAGENTA:
		{
			Output += VOLUND_LOGGERCOLOR_MAGENTA;
		}
		break;
		case LoggerColor::WHITE:
		{
			Output += VOLUND_LOGGERCOLOR_WHITE;
		}
		break;
		}

		Output += FormatString(Format, Args);

		return Output;
	}

	std::string Logger::FormatString(const char* Format, std::va_list Args) const
	{
		size_t Size = std::vsnprintf(nullptr, 0, Format, Args) + 1;
		std::string FormatedString;
		FormatedString.resize(Size);
		std::vsnprintf(FormatedString.data(), Size, Format, Args);

		return FormatedString;
	}

} //namespace Volund
