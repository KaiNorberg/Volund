#include "PCH/PCH.h"
#include "LuaEntity.h"

#include "Scene/Component/Components.h"

#include "Lua/LuaComponent/LuaComponent.h"
#include "Lua/LuaMaterial/LuaMaterial.h"
#include "Lua/LuaMesh/LuaMesh.h"
#include "Lua/LuaScene/LuaScene.h"

namespace Volund
{
	void LuaEntity::AddComponent(sol::this_state S, LuaComponentID Component, sol::table Table)
	{
		this->_Scene->AddComponent(S, this->_Entity, Component, Table);
	}

	void LuaEntity::DeleteComponent(sol::this_state S, LuaComponentID Component, uint64_t I)
	{
		this->_Scene->DeleteComponent(S, this->_Entity, Component, I);
	}

	bool LuaEntity::HasComponent(sol::this_state S, LuaComponentID Component)
	{
		return this->_Scene->HasComponent(S, this->_Entity, Component);
	}

	uint64_t LuaEntity::ComponentAmount(sol::this_state S, LuaComponentID Component)
	{
		return this->_Scene->ComponentAmount(S, this->_Entity, Component);
	}

	sol::table LuaEntity::GetComponent(sol::this_state S, LuaComponentID Component, uint64_t I)
	{
		return this->_Scene->GetComponent(S, this->_Entity, Component, I);
	}

	LuaEntity::LuaEntity(LuaScene* ThisScene, Entity entity)
	{
		this->_Scene = ThisScene;
		this->_Entity = entity;
	}
}