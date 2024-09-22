#pragma once

#include "SerialTable/SerialTable.h"

namespace Volund
{
    class Deserializer
    {
    public:

        bool Valid();

        template<typename T>
        bool Is(std::string const& key) const;

        PrimitiveSerialObject& operator[](std::string const& key);

        const SerialTable::const_iterator begin() const;
        const SerialTable::const_iterator end() const;

        SerialTable::iterator begin();
        SerialTable::iterator end();

        Deserializer(std::string const& filepath, std::string const& fileType);

        virtual ~Deserializer();

    private:

        bool m_Valid = false;

        SerialTable m_Table;
    };

    template<typename T>
    inline bool Deserializer::Is(std::string const& key) const
    {
        return this->m_Table.Is<T>(key);
    }
}
