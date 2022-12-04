#include "PCH/PCH.h"
#include "Script.h"

#include "Lua/Lua.h"

#include "Filesystem/Filesystem.h"

namespace Volund
{
	void Script::OnUpdate(TimeStep TS)
	{	
		std::string Script = "Update(" + std::to_string(this->GetEntity()) + ", " + std::to_string(TS) + ")";

		sol::function Function = (*this->_Lua)["Update"];
		Function.call<void>(Lua::LuaEntity(this->GetEntity()), TS.GetSeconds());
	}

	Script::Script(std::string Filepath)
	{
		this->_Lua = Ref<sol::state>(new sol::state());
		Lua::Connect(*this->_Lua.get());
		this->_Lua->script(Filesystem::LoadFile(Filepath));
	}
}