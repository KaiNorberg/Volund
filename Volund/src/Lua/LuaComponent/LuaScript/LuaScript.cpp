#include "PCH/PCH.h"
#include "LuaScript.h"

#include "Scene/Component/Components.h"

#include "Lua/LuaMaterial/LuaMaterial.h"
#include "Lua/LuaMesh/LuaMesh.h"

namespace Volund
{
	LuaScript::LuaScript(Ref<Script> Script)
	{
		this->_Script = Script;
	}
}