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

        std::tuple<sol::table, sol::table> result = LuaUtils::ScriptFile(this->m_SolState, filepath);
        sol::table configTable = std::get<0>(result);
        sol::table sceneTable = std::get<1>(result);

        if (!configTable.is<sol::table>())
        {
            VOLUND_WARNING("The supplied file returns a configTable of a non table type!");
            return;
        }
        if (!sceneTable.is<sol::table>())
        {
            VOLUND_WARNING("The supplied file returns a sceneTable of a non table type!"); 
            return;
        }

        /*for (auto& [key, value] : configTable)
        {
            std::string keyString = key.as<std::string>();

            if (ConfigSetters.contains(keyString))
            {
                ConfigSetters[keyString](this, value);
            }
        }*/

        this->m_Scene = std::make_shared<Scene>();

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
                    VOLUND_WARNING("Component found in scene file is of a non table type!");
                    return;
                }

                sol::table componentTable = sol::table(component);

                LuaUtils::AddComponentToEntity(this->m_Scene, newEntity, componentTable);
            }
        }
    }
}