#pragma once

#include "Scene/Scene.h"

#define VOLUND_SERIAL_FILE_TYPE "FileType"
#define VOLUND_SERIAL_DATA "Data"

#define VOLUND_SERIAL_FILE_TYPE_MATERIAL "Material"
#define VOLUND_SERIAL_FILE_TYPE_SCENE "Scene"

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
    //Entity DeserializeEntity(Ref<Scene> scene, sol::table entityTable);

    //void DeserializeScene(Ref<Scene> scene, sol::table sceneTable);

    sol::protected_function_result ScriptFile(Ref<sol::state> state, const std::string& filepath);
}