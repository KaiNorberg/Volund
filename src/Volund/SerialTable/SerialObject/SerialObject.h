#pragma once

#include "Utils/Utils.h"
#include "Logger.h"

#include <cstdint>

namespace Volund
{
    class SerialTable;

    class PrimitiveSerialObject
    {
    public:

        template<typename T>
        void operator=(T data);

        template<typename T>
        operator T();

        template<typename T>
        bool Is();

        template<typename T>
        T As();

        template<typename T>
        T* Get();

        virtual uint64_t GetTypeHash() const = 0;

    private:

    };

    template<typename T>
    class SerialObject : public PrimitiveSerialObject
    {
    public:
        
        void Set(const T& data);

        T& Get();

        const T& Get() const;

        uint64_t GetTypeHash() const override;

        SerialObject(const T& data);

    private:

        T m_Data;
    };

    template<typename T>
    inline bool PrimitiveSerialObject::Is()
    {
        //VOLUND_SERIAL_TYPE_ASSERT(T);

        return this->GetTypeHash() == Utils::GetTypeId<T>();
    }   

    template<typename T>
    inline void PrimitiveSerialObject::operator=(T data)
    {
        //VOLUND_SERIAL_TYPE_ASSERT(T);

        if (!this->Is<T>())
        {
            VOLUND_ERROR("Attempt to set PrimitiveSerialObject with incorrect type!");
        }

        ((SerialObject<T>*)this)->Set(data);
    }

    template<typename T>
    PrimitiveSerialObject::operator T()
    {
        //VOLUND_SERIAL_TYPE_ASSERT(T);

        return this->As<T>();
    }

    template<typename T>
    inline T PrimitiveSerialObject::As()
    {
        //VOLUND_SERIAL_TYPE_ASSERT(T);

        if (!this->Is<T>())
        {
            VOLUND_ERROR("Wrong type requested from PrimitiveSerialObject!");
        }

        return ((SerialObject<T>*)this)->Get();
    }

    template<typename T>
    inline T* PrimitiveSerialObject::Get()
    {
        return &((SerialObject<T>*)this)->Get();
    }

    template<typename T>
    inline const T& SerialObject<T>::Get() const
    {
        //VOLUND_SERIAL_TYPE_ASSERT(T);

        return this->m_Data;
    }

    template<typename T>
    inline void SerialObject<T>::Set(const T& data)
    {
        this->m_Data = data;
    }

    template<typename T>
    inline T& SerialObject<T>::Get()
    {
        //VOLUND_SERIAL_TYPE_ASSERT(T);

        return this->m_Data;
    }

    template<typename T>
    inline uint64_t SerialObject<T>::GetTypeHash() const
    {
        //VOLUND_SERIAL_TYPE_ASSERT(T);

        return Utils::GetTypeId<T>();
    }

    template<typename T>
    inline SerialObject<T>::SerialObject(const T& data)
    {
        //VOLUND_SERIAL_TYPE_ASSERT(T);

        this->m_Data = data;
    }
}

