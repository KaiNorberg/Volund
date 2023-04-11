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

        if (sceneTable == sol::nil)
        {
            VOLUND_WARNING("Scene file does not return a table!");
            return;
        }

        if (!sceneTable.is<sol::table>())
        {
            VOLUND_WARNING("Scene file returns a non table type!");
            return;
        }

        for (auto& [entityKey, entity] : sceneTable)
        {                        
            if (entity == sol::nil || !entity.is<sol::table>())
            {
                VOLUND_WARNING("Invalid entity found in scene file!");
                return;
            }

            auto newEntity = this->m_Scene->RegisterNewEntity();

            sol::table entityTable = sol::table(entity);
            for (auto& [componentKey, component] : entityTable)
            {   
                if (component == sol::nil || !component.is<sol::table>())
                {
                    VOLUND_WARNING("Component found in scene file is not a table!");
                    return;
                }             

                sol::table componentTable = sol::table(component);            
                
                LuaUtils::AddComponentToEntity(this->m_Scene, newEntity, componentTable);
            }
        }
    }
}