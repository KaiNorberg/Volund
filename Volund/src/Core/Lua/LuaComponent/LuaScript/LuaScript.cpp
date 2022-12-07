#include "PCH/PCH.h"
#include "LuaScript.h"

#include "Core/Scene/Component/Components.h"

#include "Core/Lua/LuaMaterial/LuaMaterial.h"
#include "Core/Lua/LuaMesh/LuaMesh.h"

namespace Volund
{
	LuaScript::LuaScript(Ref<Script> Script)
	{
		this->_Script = Script;
	}
}