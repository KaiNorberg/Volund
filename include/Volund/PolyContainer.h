#pragma once

#include <memory>
#include <unordered_map>
#include <vector>

namespace Volund
{
    /// <summary>
    /// Short for polymorphic container, a PolyContainer class VOLUND_API can store any type that can be type cast from T.
    /// </summary>
    template<typename T>
    class VOLUND_API PolyContainer
    {
    public:
        template<typename D>
        void PushBack(const D& entry);
        template<typename D>
        void PushBack(std::shared_ptr<D> entry);
        template<typename D>
        void PushBack(D* entry);
        template<typename D>
        void Erase(uint64_t index = 0);
        template<typename D>
        std::shared_ptr<D> Get(uint64_t index = 0);
        template<typename D>
        bool Contains();
        template<typename D>
        uint64_t Size();
        template<typename D>
        std::vector<std::shared_ptr<T>>& View();
        std::unordered_map<uint64_t, std::vector<std::shared_ptr<T>>>::iterator begin();
        std::unordered_map<uint64_t, std::vector<std::shared_ptr<T>>>::iterator end();
        std::unordered_map<uint64_t, std::vector<std::shared_ptr<T>>>::const_iterator begin() const;
        std::unordered_map<uint64_t, std::vector<std::shared_ptr<T>>>::const_iterator end() const;
    private:
        std::unordered_map<uint64_t, std::vector<std::shared_ptr<T>>> m_data;
    };

    template<typename T>
    template<typename D>
    inline void PolyContainer<T>::PushBack(const D& entry)
    {
        static uint64_t typeId = Utils::GetTypeId<D>();

        this->m_data[typeId].push_back(std::make_shared<D>(entry));
    }

    template<typename T>
    template<typename D>
    inline void PolyContainer<T>::PushBack(std::shared_ptr<D> entry)
    {
        static uint64_t typeId = Utils::GetTypeId<D>();

        this->m_data[typeId].push_back(entry);
    }

    template<typename T>
    template<typename D>
    inline void PolyContainer<T>::PushBack(D* entry)
    {
        static uint64_t typeId = Utils::GetTypeId<D>();

        this->m_data[typeId].push_back(std::shared_ptr<D>(entry));
    }

    template<typename T>
    template<typename D>
    inline void PolyContainer<T>::Erase(uint64_t index)
    {
        static uint64_t typeId = Utils::GetTypeId<D>();

        if (this->m_data.contains(typeId) && this->m_data[typeId].size() > index)
        {
            this->m_data[typeId].erase(this->m_data[typeId].begin() + index);
        }
    }

    template<typename T>
    template<typename D>
    inline std::shared_ptr<D> PolyContainer<T>::Get(uint64_t index)
    {
        static uint64_t typeId = Utils::GetTypeId<D>();

        return std::dynamic_pointer_cast<D>(this->m_data[typeId][index]);
    }

    template<typename T>
    template<typename D>
    inline bool PolyContainer<T>::Contains()
    {
        static uint64_t typeId = Utils::GetTypeId<D>();

        return this->m_data.contains(typeId);
    }

    template<typename T>
    template<typename D>
    inline uint64_t PolyContainer<T>::Size()
    {
        static uint64_t typeId = Utils::GetTypeId<D>();

        return this->m_data[typeId].size();
    }

    template<typename T>
    template<typename D>
    inline std::vector<std::shared_ptr<T>>& PolyContainer<T>::View()
    {
        static uint64_t typeId = Utils::GetTypeId<D>();

        return this->m_data[typeId];
    }

    template<typename T>
    inline std::unordered_map<uint64_t, std::vector<std::shared_ptr<T>>>::iterator PolyContainer<T>::begin()
    {
        return this->m_data.begin();
    }

    template<typename T>
    inline std::unordered_map<uint64_t, std::vector<std::shared_ptr<T>>>::iterator PolyContainer<T>::end()
    {
        return this->m_data.end();
    }

    template<typename T>
    inline std::unordered_map<uint64_t, std::vector<std::shared_ptr<T>>>::const_iterator PolyContainer<T>::begin() const
    {
        return this->m_data.begin();
    }

    template<typename T>
    inline std::unordered_map<uint64_t, std::vector<std::shared_ptr<T>>>::const_iterator PolyContainer<T>::end() const
    {
        return this->m_data.end();
    }
}
