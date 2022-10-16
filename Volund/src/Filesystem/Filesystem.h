#pragma once

namespace Volund
{
	class Filesystem
	{
	public:

		static std::string Load(const std::string& Filepath);

		static bool IsResource(const std::string& FileName);

		static const std::string& GetResource(const std::string& FileName);

		static std::unordered_map<std::string, std::string>::const_iterator begin();
		static std::unordered_map<std::string, std::string>::const_iterator end();

	private:

		static std::unordered_map<std::string, std::string> _Resources;
	};
}