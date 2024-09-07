#pragma once

#include "SerialTable/SerialTable.h"

namespace Volund 
{
    class Deserializer
    {
    public:

        bool Valid();

        template<typename T>
        bool Is(const std::string& key) const;

        PrimitiveSerialObject& operator[](const std::string& key);

        const SerialTable::const_iterator begin() const;
        const SerialTable::const_iterator end() const;

        SerialTable::iterator begin();
        SerialTable::iterator end();

        Deserializer(const std::string& filepath, const std::string& fileType);

        virtual ~Deserializer();

    private:

        bool m_Valid = false;

        SerialTable m_Table;
    };

    template<typename T>
    inline bool Deserializer::Is(const std::string& key) const
    {
        return this->m_Table.Is<T>(key);
    }
}

