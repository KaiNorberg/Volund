#pragma once

namespace Volund
{
	class Factory
	{
	public:

		static bool IsResource(const std::string& FileName);

		static const char* GetResource(const std::string& FileName);

		std::unordered_map<std::string, const char*>::const_iterator begin() const;
		std::unordered_map<std::string, const char*>::const_iterator end() const;

	private:

		static std::unordered_map<std::string, const char*> _Resources;

	};
}