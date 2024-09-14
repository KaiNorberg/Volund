#include "PCH/PCH.h"

#include "LuaEntity.h"

namespace Volund
{
	LuaEntity::LuaEntity(Entity entity, std::shared_ptr<Scene> scene)
	{
		this->m_Entity = entity;
		this->m_Scene = scene;
	}
}
