#pragma once

namespace Volund
{
	class Filesystem;

	class File
	{
	public:

		std::string String();

		bool GetLine(std::string& line);

	private:
		friend class Filesystem;

		File(const std::string& content);

		std::istringstream m_StringStream;
	};

	class Filesystem
	{
	public:

		static Ref<File> Load(const std::string& filepath);

		static void Write(const std::string& filepath, const std::string& content);

	private:

		Filesystem();

		static Ref<File> GetResource(const std::string& filepath);

		static bool IsResource(const std::string& filepath);

		static void CreateResource(const std::string& filepath, const char* content);

		static inline std::unordered_map<std::string, Ref<File>> m_Resources;
	};
}