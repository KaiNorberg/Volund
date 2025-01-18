#pragma once

#include "Lua/LuaTypes.h"

#define VOLUND_SERIAL_DATA "Data"
#define VOLUND_SERIAL_FILE_TYPE "FileType"

namespace Volund
{
    class Serializer
    {
    public:

        void WriteToFile(std::string const& filepath);

        std::string GetOutput();

        void StartTable(std::string const& name = "");
        void EndTable();

        void Insert(std::string const& name, LuaInt value);
        void Insert(std::string const& name, LuaFloat value);
        void Insert(std::string const& name, LuaBool value);
        void Insert(std::string const& name, const LuaString& value, bool asString = true);
        void Insert(std::string const& name, const LuaVec2& value);
        void Insert(std::string const& name, const LuaVec3& value);
        void Insert(std::string const& name, const Vec4& value);

        Serializer(std::string const& fileType);

    private:

        void InsertName(std::string const& name);

        void Indent();

        uint8_t m_Indentation = 1;

        std::string m_FileType;

        std::string m_Output = "";
    };
}
