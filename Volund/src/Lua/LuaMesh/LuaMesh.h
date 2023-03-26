#pragma once

#include "Renderer/Mesh/Mesh.h"

namespace Volund
{
	struct LuaMesh
	{
	public:

		int Padding = NULL;

		Ref<Mesh> Get();

		LuaMesh(Ref<Mesh> mesh);

		LuaMesh(const std::string& filepath);

	private:

		Ref<Mesh> m_Mesh;
	};
}