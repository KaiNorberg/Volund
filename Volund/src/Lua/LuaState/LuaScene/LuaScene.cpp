#include "PCH/PCH.h"
#include "LuaScene.h"

#include "Filesystem/Filesystem.h"

#include <sol/sol.hpp>
#include "Lua/LuaUtils/LuaUtils.h"

namespace Volund
{
    Ref<Scene> LuaScene::Get()
    {
        return this->m_Scene;
    }

    LuaScene::LuaScene(const std::string& filepath)
    {           		
        VOLUND_INFO("Loading scene (%s)...", filepath.c_str());

        std::string script = Filesystem::Load(filepath);

        sol::table sceneTable = LuaUtils::ScriptFile(this->m_SolState, filepath);

        this->m_Scene = std::make_shared<Scene>();

        VOLUND_ASSERT(sceneTable != sol::nil && sceneTable.is<sol::table>(), "Scene files must return a valid Lua table!");
        for (auto& [entityKey, entity] : sceneTable)
        {                
            VOLUND_ASSERT(entity != sol::nil && entity.is<sol::table>(), "Invalid entity found in scene file!");

            auto newEntity = this->m_Scene->RegisterNewEntity();

            sol::table entityTable = sol::table(entity);
            for (auto& [componentKey, component] : entityTable)
            {                        
                VOLUND_ASSERT(component != sol::nil && component.is<sol::table>(), "Component found in scene file is not a table!");
                sol::table componentTable = sol::table(component);            
                
                LuaUtils::AddComponentToEntity(this->m_Scene, newEntity, componentTable);
            }
        }
    }
}