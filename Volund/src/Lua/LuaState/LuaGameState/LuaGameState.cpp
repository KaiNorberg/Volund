#include "PCH/PCH.h"
#include "LuaGameState.h"

#include "Filesystem/Filesystem.h"

#include <sol/sol.hpp>
#include "Lua/LuaUtils/LuaUtils.h"

namespace Volund
{
    using ConfigSetterFunc = void(*)(Ref<Window>, sol::object);

    void CursorEnabledSetter(Ref<Window> window, sol::object value)
    {
        window->SetCursorEnabled(value.as<bool>());
    }

    void VsyncSetter(Ref<Window> window, sol::object value)
    {
        window->SetVsync(value.as<bool>());
    }

    std::unordered_map<std::string, ConfigSetterFunc> configSetters =
    {
        {"CursorEnabled", CursorEnabledSetter},
        {"Vsync", VsyncSetter}
    };

    Ref<GameState> LuaGameState::Get()
    {
        return this->m_GameState;
    }

    LuaGameState::LuaGameState(Ref<Window> window, const std::string& filepath)
    {           		
        VOLUND_INFO("Loading Scene %s", filepath.c_str());

        this->m_GameState = std::make_shared<GameState>(window, filepath);

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

        for (auto& [key, value] : configTable)
        {
            std::string keyString = key.as<std::string>();

            if (configSetters.contains(keyString))
            {
                configSetters[keyString](window, value);
            }
        }

        auto scene = this->m_GameState->GetScene();

        for (auto& [entityKey, entity] : sceneTable)
        {
            if (!entity.is<sol::table>())
            {
                VOLUND_WARNING("Invalid entity found in scene file!");
                return;
            }

            auto newEntity = scene->RegisterNewEntity();

            sol::table entityTable = sol::table(entity);
            for (auto& [componentKey, component] : entityTable)
            {
                if (!component.is<sol::table>())
                {
                    VOLUND_WARNING("Component found in scene file is of a non table type!");
                    return;
                }

                sol::table componentTable = sol::table(component);

                LuaUtils::AddComponentToEntity(scene, newEntity, componentTable);
            }
        }
    }
}