#include "ResourceLibrary/ResourceLibrary.hpp"

namespace Volund
{
	bool ResourceLibrary::IsResource(std::string const& filepath)
	{
		ResourceLibrary singleton;

		return m_resources.contains(filepath);
	}

	const char* ResourceLibrary::Fetch(std::string const& filepath)
    {
		if (IsResource(filepath))
		{
			return m_resources[filepath];
		}
		else
		{
			return nullptr;
		}
    }

	const std::unordered_map<std::string, const char*>& ResourceLibrary::Map()
	{
		return m_resources;
	}

	void ResourceLibrary::CreateResource(std::string const& filepath, const char* content)
	{
		m_resources[filepath] = content;
	}

	ResourceLibrary::ResourceLibrary()
    {
		CreateResource("://Simple.shader",
			#include "Resources/Shaders/Simple.shader"
		);
		CreateResource("://SimpleTexture.shader",
			#include "Resources/Shaders/SimpleTexture.shader"
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