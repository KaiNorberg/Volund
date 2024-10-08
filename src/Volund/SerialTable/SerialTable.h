#pragma once

#include "SerialObject/SerialObject.h"

namespace Volund
{
    class SerialTable
    {
    public:

        using iterator = std::unordered_map<std::string, std::shared_ptr<PrimitiveSerialObject>>::iterator;
        using const_iterator = std::unordered_map<std::string, std::shared_ptr<PrimitiveSerialObject>>::const_iterator;

        void Erase(const std::string& key);

        void Rename(const std::string& key, const std::string& newKey);

        template<typename T>
        void Insert(const std::string& key, const T& value);

        template<typename T>
        bool Is(const std::string& key) const;

        template<typename T>
        bool Contains(const std::string& key) const;

        PrimitiveSerialObject& operator[](const std::string& key);

        const SerialTable::const_iterator begin() const;

        const SerialTable::const_iterator end() const;

        SerialTable::iterator begin();

        SerialTable::iterator end();

    private:

        std::unordered_map<std::string, std::shared_ptr<PrimitiveSerialObject>> m_Table;
    };

    template<typename T>
    bool SerialTable::Contains(const std::string& key) const
    {
        return this->m_Table.contains(key) && this->m_Table.at(key)->Is<T>();
    }

    template<typename T>
    inline void SerialTable::Insert(const std::string& key, const T& value)
    {
        this->m_Table[key] = std::make_shared<SerialObject<T>>(value);
    }

    template<typename T>
    inline bool SerialTable::Is(const std::string& key) const
    {
        return this->m_Table.at(key)->GetTypeHash() == Utils::GetTypeId<T>();
    }
}
