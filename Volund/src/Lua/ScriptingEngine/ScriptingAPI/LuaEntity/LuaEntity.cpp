#include "PCH/PCH.h"

#include "LuaEntity.h"

namespace Volund
{
	LuaEntity::LuaEntity(Entity entity, Ref<Scene> scene)
	{
		this->m_Entity = entity;
		this->m_Scene = scene;
	}
}