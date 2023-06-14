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

	void ResourceLibrary::CreateResource(const std::string& filepath, const char* content)
	{
		m_Resources[filepath] = content;
	}

	ResourceLibrary::ResourceLibrary()
    {
		CreateResource("://Shaders/Simple.shader",
			#include "Resources/Shaders/Simple.shader"
		);
		CreateResource("://Shaders/SimpleTexture.shader",
			#include "Resources/Shaders/SimpleTexture.shader"
		);
		CreateResource("://Shaders/PBR.shader",
			#include "Resources/Shaders/PBR.shader"
		);
		CreateResource("://Shaders/PBRTexture.shader",
			#include "Resources/Shaders/PBRTexture.shader"
		);
		CreateResource("://Meshes/Sphere.obj",
			#include "Resources/Meshes/Sphere.obj"
		);
		CreateResource("://Meshes/Cube.obj",
			#include "Resources/Meshes/Cube.obj"
		);
		CreateResource("://Meshes/Quad.obj",
			#include "Resources/Meshes/Quad.obj"
		);
	}
}
