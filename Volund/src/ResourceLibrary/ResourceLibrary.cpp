#include "PCH/PCH.h"
#include "ResourceLibrary.h"

namespace Volund
{
	bool ResourceLibrary::IsResource(const std::string& filepath)
	{
		ResourceLibrary singleton;

		return m_Resources.contains(filepath);
	}

	const char* ResourceLibrary::Fetch(const std::string& filepath)
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

	const std::unordered_map<std::string, const char*>& ResourceLibrary::Map()
	{
		return m_Resources;
	}

	void ResourceLibrary::CreateResource(const std::string& filepath, const char* content)
	{
		m_Resources[filepath] = content;
	}

	ResourceLibrary::ResourceLibrary()
    {
		CreateResource("://Simple.shader",
			#include "Resources/Shaders/Simple.shader"
		);
		CreateResource("://SimpleTexture.shader",
			#include "Resources/Shaders/SimpleTexture.shader"
		);
		CreateResource("://PBR.shader",
			#include "Resources/Shaders/PBR.shader"
		);
		CreateResource("://PBRTexture.shader",
			#include "Resources/Shaders/PBRTexture.shader"
		);
		CreateResource("://Sphere.obj",
			#include "Resources/Meshes/Sphere.obj"
		);
		CreateResource("://Cube.obj",
			#include "Resources/Meshes/Cube.obj"
		);
		CreateResource("://Quad.obj",
			#include "Resources/Meshes/Quad.obj"
		);
	}
}
