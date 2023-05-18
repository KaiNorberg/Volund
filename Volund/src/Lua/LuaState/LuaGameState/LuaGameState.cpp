#include "PCH/PCH.h"
#include "LuaGameState.h"

#include "Filesystem/Filesystem.h"

#include <sol/sol.hpp>
#include "Lua/LuaUtils/LuaUtils.h"

namespace Volund
{
    Ref<GameState> LuaGameState::Get()
    {
        return this->m_GameState;
    }

    LuaGameState::LuaGameState(Ref<Window> window, const std::string& filepath)
    {           		
        VOLUND_INFO("Loading GameState %s", filepath.c_str());

        this->m_GameState = std::make_shared<GameState>(window, filepath);

        sol::table sceneTable = LuaUtils::ScriptFile(this->m_SolState, filepath);

        if (!sceneTable.is<sol::table>())
        {
            VOLUND_WARNING("The supplied file returns a sceneTable of a non table type!"); 
            return;
        }

        LuaUtils::DeserializeScene(this->m_GameState->GetScene(), sceneTable);
    }
}