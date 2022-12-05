#pragma once

#include "Scene/Scene.h"
#include "Renderer/Material/Material.h"
#include "Renderer/Mesh/Mesh.h"

#include "Scene/Component/Components.h"

namespace Volund
{
	class Lua
	{
	public:

		static void Connect(sol::state& Lua);

		static sol::object LuaRequire(sol::this_state S, std::string Filepath);

		static void LuaPrint(std::string String);
	};
}

