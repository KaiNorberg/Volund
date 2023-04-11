#include "PCH/PCH.h"
#include "LuaAssetLoader.h"

#include "Filesystem/Filesystem.h"
#include "Lua/LuaVec/LuaVec.h"

#include "Scene/AssetCache/AssetCache.h"

#include <sol/sol.hpp>
#include "Lua/LuaUtils/LuaUtils.h"

namespace Volund
{
    template<>
    LuaAssetLoader<Material>::LuaAssetLoader(AssetCache* assetCache, const std::string& filepath)
    {
        VOLUND_INFO("Loading Material (%s)...", filepath.c_str());

        std::string script = Filesystem::Load(filepath);

        sol::table materialTable = LuaUtils::ScriptFile(this->m_SolState, filepath);

        if (materialTable == sol::nil)
        {
            VOLUND_WARNING("Material file does not return a table!");
            return;
        }

        if (!materialTable.is<sol::table>() || materialTable.size() < 1)
        {
            VOLUND_WARNING("Material files must return a valid Lua table!");
            return;
        }

        std::string shaderFilepath = materialTable[1];

        //TODO: Add asset lib
        auto shader = Shader::Create(shaderFilepath);

        this->m_Data = Material::Create(shader);

        bool first = true;
        for (auto& [key, value] : materialTable)
        {
            if (first)
            {
                first = false;
                continue;
            }
            
            std::string keyString = key.as<std::string>();

            //TODO: Add texture and framebuffer
            if (value.is<uint64_t>())
            {
                this->m_Data->SetInt(keyString, value.as<uint64_t>());
            }
            else if (value.is<double>())
            {
                this->m_Data->SetDouble(keyString, value.as<double>());
            }
            else if (value.is<LuaVec2>())
            {
                this->m_Data->SetVec2(keyString, value.as<LuaVec2>().GLM());
            }
            else if (value.is<LuaVec3>())
            {
                this->m_Data->SetVec3(keyString, value.as<LuaVec3>().GLM());
            }
            else if (value.is<LuaVec4>())
            {
                this->m_Data->SetVec4(keyString, value.as<LuaVec4>().GLM());
            }
            else if (value.is<std::string>())
            {
                auto texture = assetCache->Fetch<Texture>(value.as<std::string>());
                this->m_Data->SetTexture(keyString, texture);
            }
        }
    }
}