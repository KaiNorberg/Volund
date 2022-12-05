#pragma once

#include "Renderer/Mesh/Mesh.h"

namespace Volund
{
	struct LuaMesh
	{
	public:

		Ref<Mesh> Get();

		LuaMesh(Ref<Mesh> Mesh);

		LuaMesh(const std::string& MeshPath);

	private:

		Ref<Mesh> _Mesh;
	};
}