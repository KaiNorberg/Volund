#include "PCH/PCH.h"
#include "LuaMesh.h"

namespace Volund
{
	Ref<Mesh> LuaMesh::Get()
	{
		return this->_Mesh;
	}

	LuaMesh::LuaMesh(Ref<Mesh> Mesh)
	{
		this->_Mesh = Mesh;
	}

	LuaMesh::LuaMesh(const std::string& MeshPath)
	{
		this->_Mesh = Mesh::Create(MeshPath);
	}	
}