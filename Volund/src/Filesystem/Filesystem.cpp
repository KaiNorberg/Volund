#include "PCH/PCH.h"
#include "Filesystem.h"

namespace Volund
{
	std::string File::String()
	{
		return this->m_StringStream.str();
	}

	bool File::GetLine(std::string& line)
	{
		auto& ret = std::getline(this->m_StringStream, line);

		if (ret)
		{
			return true;
		}
		else
		{
			this->m_StringStream.clear();
			this->m_StringStream.seekg(0);
			return false;
		}
	}

	File::File(const std::string& filepath)
	{
		this->m_StringStream = std::istringstream(filepath);
	}

	Ref<File> Filesystem::Load(const std::string& filepath)
    {
		if (IsResource(filepath))
		{
			return GetResource(filepath);
		}		
		
		auto file = std::ifstream(filepath);

		if (!file)
		{
			VOLUND_WARNING("Unable to load file %s.", filepath.c_str());	
			return nullptr;
		}
		
		std::string line;
		std::string output;
		while (std::getline(file, line))
		{
			output += line + '\n';
		}
		return Ref<File>(new File(output));
    }

	void Filesystem::Write(const std::string& filepath, const std::string& content)
	{
		std::ofstream out(filepath);
		out << content;
		out.close();
	}

	Ref<File> Filesystem::GetResource(const std::string& filepath)
	{
		if (IsResource(filepath))
		{
			return m_Resources[filepath];
		}
		else
		{
			return nullptr;
		}
	}

	bool Filesystem::IsResource(const std::string& filepath)
	{
		static Filesystem singleTon;

		return m_Resources.contains(filepath);
	}

	void Filesystem::CreateResource(const std::string& filepath, const char* content)
	{
		m_Resources[filepath] = Ref<File>(new File(content));
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
