#pragma once

namespace Volund
{
	class Filesystem
	{
	public:

		static void WriteFile(const std::string& filepath, const std::string& file);

		static std::string LoadFile(const std::string& filepath);

		static std::string LoadResource(const std::string& filepath);

		static bool IsResource(const std::string& filepath);

		static void CreateResource(const std::string& filepath, const char* content);

		static void AddRelativeFilepath(const std::string& filepath);

		static void RemoveRelativeFilepath(const std::string& filepath);

		static std::string GetFinalPath(const std::string& filepath);

	private:

		Filesystem();

		static inline std::vector<std::string> m_RelativeFilepaths;

		static inline std::unordered_map<std::string, const char*> m_Resources;
	};
}