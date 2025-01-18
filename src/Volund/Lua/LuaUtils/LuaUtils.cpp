#include "Scene/Component/Components.h"

#include "Audio/AudioBuffer/AudioBuffer.h"

#include "LuaUtils.h"
#include "Lua/LuaTypes.h"

#include <sol/sol.hpp>

namespace Volund::LuaUtils
{
    SerialTable DeserializeTable(sol::table table)
    {
        SerialTable out;

        for (auto& [key, value] : table)
        {
            switch (value.get_type())
            {
            case sol::type::number:
            {
                if (value.is<LuaInt>())
                {
                    out.Insert(key.as<std::string>(), value.as<LuaInt>());
                }
                else if (value.is<LuaFloat>())
                {
                    out.Insert(key.as<std::string>(), value.as<LuaFloat>());
                }
            }
            break;
            case sol::type::boolean:
            {
                out.Insert(key.as<std::string>(), value.as<LuaBool>());
            }
            break;
            case sol::type::string:
            {
                out.Insert(key.as<std::string>(), value.as<LuaString>());
            }
            break;
            case sol::type::userdata:
            {
                if (value.is<Vec2>())
                {
                    out.Insert(key.as<std::string>(), value.as<Vec2>());
                }
                else if (value.is<Vec3>())
                {
                    out.Insert(key.as<std::string>(), value.as<Vec3>());
                }
                else if (value.is<Vec4>())
                {
                    out.Insert(key.as<std::string>(), value.as<Vec4>());
                }
            }
            break;
            case sol::type::table:
            {
                out.Insert(key.as<std::string>(), DeserializeTable(value.as<sol::table>()));
            }
            break;
            }
        }

        return out;
    }

    sol::protected_function_result ScriptFile(std::shared_ptr<sol::state> state, const std::string &filepath)
    {
        sol::protected_function_result result;
        try
		{
            result = state->script_file(filepath, [](lua_State*, sol::protected_function_result pfr)
			{
				sol::error err = pfr;
				VOLUND_WARNING(err.what());

				return pfr;
			});
		}
		catch(const sol::error& e)
		{
			VOLUND_WARNING(e.what());
		}

        return result;
    }
}
