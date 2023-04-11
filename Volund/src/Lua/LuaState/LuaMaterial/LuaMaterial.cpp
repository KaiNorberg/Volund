#include "PCH/PCH.h"
#include "LuaMaterial.h"

#include "Filesystem/Filesystem.h"
#include "Lua/LuaVec/LuaVec.h"

#include <sol/sol.hpp>
#include "Lua/LuaUtils/LuaUtils.h"

namespace Volund
{
    Ref<Material> LuaMaterial::Get()
    {
        return this->m_Material;
    }

    LuaMaterial::LuaMaterial(const std::string &filepath)
    {
        VOLUND_INFO("Loading material (%s)...", filepath.c_str());

        std::string script = Filesystem::Load(filepath);

        sol::table materialTable = LuaUtils::ScriptFile(this->m_SolState, filepath);

        VOLUND_ASSERT(materialTable != sol::nil && materialTable.is<sol::table>() && materialTable.size() >= 1, "Material files must return a valid Lua table!");
        
        std::string shaderFilepath = materialTable[1];

        //TODO: Add asset lib
        auto shader = Shader::Create(shaderFilepath);

        this->m_Material = Material::Create(shader);

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
                this->m_Material->SetInt(keyString, value.as<uint64_t>());
            }
            else if (value.is<double>())
            {
                this->m_Material->SetDouble(keyString, value.as<double>());
            }
            else if (value.is<LuaVec2>())
            {
                this->m_Material->SetVec2(keyString, value.as<LuaVec2>().GLM());
            }
            else if (value.is<LuaVec3>())
            {
                this->m_Material->SetVec3(keyString, value.as<LuaVec3>().GLM());
            }
            else if (value.is<LuaVec4>())
            {
                this->m_Material->SetVec4(keyString, value.as<LuaVec4>().GLM());
            }
        }
    }

    Ref<LuaMaterial> LuaMaterial::Create(const std::string &filepath)
    {
        return std::make_shared<LuaMaterial>(filepath);
    }
}