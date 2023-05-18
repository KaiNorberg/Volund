#include "PCH/PCH.h"
#include "Filesystem.h"

namespace Volund
{    
	Ref<FilesystemLink> FilesystemLink::Create(const std::string& relativeFilepath)
    {
        auto newLink = std::make_shared<FilesystemLink>();
		newLink->m_RelativeFilepath = relativeFilepath;

		Filesystem::AddLink(relativeFilepath);

		return newLink;
    }

    std::string FilesystemLink::GetRelativeFilepath()
    {
        return this->m_RelativeFilepath;
    }

    FilesystemLink::~FilesystemLink()
    {
		Filesystem::RemoveLink(this->m_RelativeFilepath);
    }

	std::string Filesystem::GetFinalPath(const std::string& filepath)
	{
		if (std::filesystem::exists(filepath))
		{
			return filepath;
		}

		for (auto& link : m_FilesystemLinks)
		{
			std::string newPath = link + "/" + filepath;

			if (std::filesystem::exists(newPath))
			{			
				return newPath;
			}
		}
		
		return filepath;
	}
    
	std::string Filesystem::Load(const std::string& filepath)
    {
		if (IsResource(filepath))
		{
			return GetResource(filepath);
		}		
		
		auto file = std::ifstream(GetFinalPath(filepath));

		if (!file)
		{
			VOLUND_WARNING("Unable to load file %s.", filepath.c_str());	
		}
		
		std::string line;
		std::string output;
		while (std::getline(file, line))
		{
			output += line + '\n';
		}
		return output;
    }

	void Filesystem::Write(const std::string& filepath, const std::string& content)
	{
		std::ofstream out(GetFinalPath(filepath));
		out << content;
		out.close();
	}

    std::string Filesystem::GetResource(const std::string& filepath)
	{
		if (IsResource(filepath))
		{
			return m_Resources[filepath];
		}
		else
		{
			return std::string();
		}
	}

	bool Filesystem::IsResource(const std::string& filepath)
	{
		static Filesystem singleTon;

		return m_Resources.contains(filepath);
	}

	void Filesystem::CreateResource(const std::string& filepath, const char* content)
	{
		m_Resources[filepath] = content;
	}

    void Filesystem::AddLink(const std::string& filepath)
    {
		m_FilesystemLinks.push_back(filepath);
    }

    void Filesystem::RemoveLink(const std::string& filepath)
    {
		for (int i = 0; i < m_FilesystemLinks.size(); i++)
		{				
			if (m_FilesystemLinks[i] == filepath)
			{
				m_FilesystemLinks.erase(m_FilesystemLinks.begin() + i);
				return;
			}
		}

		VOLUND_WARNING("Unable to remove FilesystemLink!");
    }

    Filesystem::Filesystem()
    {
		CreateResource("://Simple.shader",
			#include "Shaders/Simple.vshader"
		);
		CreateResource("://SimpleTexture.shader",
			#include "Shaders/SimpleTexture.vshader"
		);
		CreateResource("://PBR.shader",
			#include "Shaders/PBR.vshader"
		);
		CreateResource("://PBRTexture.shader",
			#include "Shaders/PBRTexture.vshader"
		);
		CreateResource("://Sphere.obj",
			#include "Meshes/Sphere.vobj"
		);
		CreateResource("://Cube.obj",
			#include "Meshes/Cube.vobj"
		);
		CreateResource("://Quad.obj",
			#include "Meshes/Quad.vobj"
		);
	}
}
