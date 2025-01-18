#pragma once

#include "SerialObject/SerialObject.h"

#include <unordered_map>

namespace Volund
{
    class SerialTable
    {
    public:

        using iterator = std::unordered_map<std::string, std::shared_ptr<PrimitiveSerialObject>>::iterator;
        using const_iterator = std::unordered_map<std::string, std::shared_ptr<PrimitiveSerialObject>>::const_iterator;

        void Erase(std::string const& key);

        void Rename(std::string const& key, std::string const& newKey);

        template<typename T>
        void Insert(std::string const& key, const T& value);

        template<typename T>
        bool Is(std::string const& key) const;

        template<typename T>
        bool Contains(std::string const& key) const;

        PrimitiveSerialObject& operator[](std::string const& key);

        const SerialTable::const_iterator begin() const;

        const SerialTable::const_iterator end() const;

        SerialTable::iterator begin();

        SerialTable::iterator end();

    private:

        std::unordered_map<std::string, std::shared_ptr<PrimitiveSerialObject>> m_Table;
    };

    template<typename T>
    bool SerialTable::Contains(std::string const& key) const
    {
        return this->m_Table.contains(key) && this->m_Table.at(key)->Is<T>();
    }

    template<typename T>
    inline void SerialTable::Insert(std::string const& key, const T& value)
    {
        this->m_Table[key] = std::make_shared<SerialObject<T>>(value);
    }

    template<typename T>
    inline bool SerialTable::Is(std::string const& key) const
    {
        return this->m_Table.at(key)->GetTypeHash() == Utils::GetTypeId<T>();
    }
}
