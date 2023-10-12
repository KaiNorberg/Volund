#pragma once

#include "SerialTable/SerialTable.h"

#define VOLUND_SERIAL_FILE_TYPE "FileType"
#define VOLUND_SERIAL_DATA "Data"

#define VOLUND_SERIAL_FILE_TYPE_MATERIAL "Material"
#define VOLUND_SERIAL_FILE_TYPE_SCENE "Scene"

#define VOLUND_SERIAL_TYPE_ASSERT(SERIAL_TYPE) static_assert(std::is_same<SERIAL_TYPE, LuaInt>::value || std::is_same<SERIAL_TYPE, LuaFloat>::value || \
std::is_same<SERIAL_TYPE, LuaBool>::value || std::is_same<SERIAL_TYPE, LuaString>::value || \
std::is_same<SERIAL_TYPE, Vec2>::value || std::is_same<SERIAL_TYPE, Vec3>::value || \
std::is_same<SERIAL_TYPE, Vec4>::value || std::is_same<SERIAL_TYPE, SerialTable>::value, "Invalid type for SerialObject!") \

namespace Volund
{
    enum class LuaComponentID
    {
        Camera = 1,
        CameraMovement = 2,
        MeshRenderer = 3,
        PointLight = 4,
        //Script = 5,
        Tag = 6,
        Transform = 7,
        SoundSource = 8,
        SoundListener = 9,
        ScriptComponent = 10
    };
}

namespace Volund::LuaUtils
{
    SerialTable DeserializeTable(sol::table table);

    sol::protected_function_result ScriptFile(Ref<sol::state> state, const std::string& filepath);
}