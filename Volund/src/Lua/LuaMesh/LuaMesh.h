#pragma once

#include "Renderer/Mesh/Mesh.h"

namespace Volund
{
	struct LuaMesh
	{
	public:

		int Padding = NULL;

		Ref<Mesh> Get();

		LuaMesh(Ref<Mesh> Mesh);

		LuaMesh(const std::string& MeshPath);

	private:

		Ref<Mesh> _Mesh;
	};
}