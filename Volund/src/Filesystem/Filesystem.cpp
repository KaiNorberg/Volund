#include "PCH/PCH.h"
#include "Filesystem.h"

namespace Volund
{
	std::string Filesystem::LoadFile(const std::string& filepath)
	{
		if (IsResource(filepath))
		{
			return LoadResource(filepath);
		}
		
		std::ifstream file(GetFinalPath(filepath));
		
		if (!file)
		{		
			VOLUND_WARNING("Unable to load file %s.", filepath.c_str());

			return "";
		}
		
		std::string line;
		std::string output;
		while (std::getline(file, line))
		{
			output += line + '\n';
		}
		return output;
	}

	void Filesystem::WriteFile(const std::string& filepath, const std::string& file)
	{
		std::ofstream stream(GetFinalPath(filepath));

		stream << file;
	}

	std::string Filesystem::LoadResource(const std::string& filepath)
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

	void Filesystem::AddRelativeFilepath(const std::string& filepath)
	{
		m_RelativeFilepaths.push_back(filepath);
	}

	void Filesystem::RemoveRelativeFilepath(const std::string& filepath)
	{
		auto it = std::find(m_RelativeFilepaths.begin(), m_RelativeFilepaths.end(), filepath);

		if (it != m_RelativeFilepaths.end())
		{
			m_RelativeFilepaths.erase(it);
		}
	}

	std::string Filesystem::GetFinalPath(const std::string& filepath)
	{
		if (std::filesystem::exists(filepath))
		{
			return filepath;
		}

		for (auto& relativePath : m_RelativeFilepaths)
		{
			std::string newPath = relativePath + "/" + filepath;

			if (std::filesystem::exists(newPath))
			{			
				return newPath;
			}
		}

		return filepath;
	}

	Filesystem::Filesystem()
	{
		CreateResource("Simple.vshader",
			#include "Shaders/Simple.vshader"
		);
		CreateResource("SimpleTexture.vshader",
			#include "Shaders/SimpleTexture.vshader"
		);
		CreateResource("PBR.vshader",
			#include "Shaders/PBR.vshader"
		);
		CreateResource("PBRTexture.vshader",
			#include "Shaders/PBRTexture.vshader"
		);
		CreateResource("Sphere.vobj",
			#include "Meshes/Sphere.vobj"
		);
		CreateResource("Cube.vobj",
			#include "Meshes/Cube.vobj"
		);
		CreateResource("Quad.vobj",
			#include "Meshes/Quad.vobj"
		);
	}
}
