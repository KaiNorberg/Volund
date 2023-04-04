#pragma once

namespace Volund
{
	class Filesystem;

	/// <summary>
	/// A FilesystemLink allows files to be loaded by the Filesystem class from the relative filepath that the FilesystemLink contains. 
	/// This only works for the lifespan of the FilesystemLink.
	/// </summary>
	class FilesystemLink
	{
	public:

		static Ref<FilesystemLink> Create(const std::string& relativeFilepath);

		std::string GetRelativeFilepath();

		~FilesystemLink();

	private:
		friend class Filesytem;

		std::string m_RelativeFilepath;
	};

	class Filesystem
	{
	public:

		static std::string GetFinalPath(const std::string& filepath);

		static std::string Load(const std::string& filepath);

		//static void Write(const std::string& filepath, const std::string& content);

	private:
		friend class FilesystemLink;

		Filesystem();

		static std::string GetResource(const std::string& filepath);

		static bool IsResource(const std::string& filepath);

		static void CreateResource(const std::string& filepath, const char* content);

		static void AddLink(const std::string& filepath);

		static void RemoveLink(const std::string& filepath);

		static inline std::vector<std::string> m_FilesystemLinks;

		static inline std::unordered_map<std::string, const char*> m_Resources;
	};
}