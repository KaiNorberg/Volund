#pragma once

#include "Core/Scene/Component/MeshRenderer/MeshRenderer.h"

#include "Core/Lua/LuaMesh/LuaMesh.h"
#include "Core/Lua/LuaMaterial/LuaMaterial.h"

#include "Core/Lua/LuaComponent/LuaComponent.h"
#include "Core/Lua/LuaComponent/LuaComponents.h"

namespace Volund
{
	struct LuaMeshRenderer
	{
	public:

		void SetMesh(LuaMesh NewMesh);
		void SetMaterial(LuaMaterial NewMaterial);

		LuaMesh GetMesh();
		LuaMaterial GetMaterial();

		LuaMeshRenderer(Ref<MeshRenderer> MeshRenderer);

	private:

		Ref<MeshRenderer> _MeshRenderer;
	};
}