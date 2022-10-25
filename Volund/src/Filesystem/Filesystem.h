#pragma once

namespace Volund
{
	class Resource
	{
	public:

		void CreateSubDir(const std::string& SubDir);

		void CreateFile(const std::string& FileName, const std::string& FileData);

		const std::string& GetData() const;

		bool Contains(const std::string& Name) const;

		std::string Extension() const;

		bool IsDirectory() const;

		Resource() = default;

		Resource(const std::string& Name, const std::string& Data = "");

		Resource& operator [](const std::string& Name);

		const std::unordered_map<std::string, Resource>::const_iterator begin() const;
		const std::unordered_map<std::string, Resource>::const_iterator end() const;

	private:

		std::unordered_map<std::string, Resource> _Children;
		std::string _Name;
		std::string _Data;
	};

	class Filesystem
	{
	public:

		static std::string Load(const std::string& Filepath);

		static Resource* GetGrandFatherResource();

	private:

		Filesystem();

		static inline Resource _GrandfatherResource = Resource(":/");
	};
}