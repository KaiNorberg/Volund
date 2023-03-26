#include "PCH/PCH.h"
#include "LuaMesh.h"

namespace Volund
{
	Ref<Mesh> LuaMesh::Get()
	{
		return this->m_Mesh;
	}

	LuaMesh::LuaMesh(Ref<Mesh> mesh)
	{
		this->m_Mesh = mesh;
	}

	LuaMesh::LuaMesh(const std::string& filepath)
	{
		this->m_Mesh = Mesh::Create(filepath);
	}	
}