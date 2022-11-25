#pragma once

namespace Volund
{
	class Filesystem
	{
	public:

		static void WriteFile(const std::string& Filepath, const std::string& File);

		static std::string LoadFile(const std::string& Filepath);

		static std::string LoadResource(const std::string& Filepath);

		static bool IsResource(const std::string& Filepath);

		static void CreateResource(const std::string& Filepath, const char* Content);

		static void AddRelativeFilepath(const std::string& Filepath);

		static void RemoveRelativeFilepath(const std::string& Filepath);

		static std::string GetFinalPath(const std::string& Filepath);

	private:

		Filesystem();

		static inline std::vector<std::string> _RelativeFilepaths;

		static inline std::unordered_map<std::string, const char*> _Resources;
	};
}