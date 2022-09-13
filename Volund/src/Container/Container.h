#pragma once

namespace Volund
{
	/// <summary>
	/// A container that can store any type that can be type cast from T.
	/// </summary>
	template<typename T>
	class Container
	{
	public:

		template <typename D>
		void PushBack(Ref<D> const& Entry);

		template <typename D>
		void Erase(uint64_t Index = 0);

		template <typename D>
		Ref<D> Get(uint64_t Index = 0) const;

		template <typename D>
		bool Contains(uint64_t Index = 0) const;

		template <typename D>
		const std::vector<Ref<T>>& View() const;

		template <typename D>
		uint64_t Size() const;

		std::vector<std::vector<Ref<T>>>::iterator begin();
		std::vector<std::vector<Ref<T>>>::iterator end();

		std::vector<std::vector<Ref<T>>>::const_iterator begin() const;
		std::vector<std::vector<Ref<T>>>::const_iterator end() const;

	private:

		template <typename D>
		uint64_t GetTypeID() const;

		static inline uint64_t _NewTypeID = 0;

		std::vector<std::vector<Ref<T>>> _Data;
	};

	template <typename T>
	template <typename D>
	inline void Container<T>::PushBack(Ref<D> const& Entry)
	{
		static uint64_t TypeID = this->GetTypeID<D>();

		this->_Data.resize(TypeID + 1);

		this->_Data[TypeID].push_back(Entry);
	}

	template <typename T>
	template <typename D>
	inline void Container<T>::Erase(uint64_t Index)
	{
		static uint64_t TypeID = this->GetTypeID<D>();

		if (!this->Contains<D>(Index))
		{
			VOLUND_ERROR("Container of type (%s) does not contain derived type (%s) with index (%d)!", typeid(T).name(), typeid(D).name(), Index);
		}

		this->_Data[TypeID].erase(Index);
	}

	template <typename T>
	template <typename D>
	inline Ref<D> Container<T>::Get(uint64_t Index) const
	{
		static uint64_t TypeID = this->GetTypeID<D>();

		if (!this->Contains<D>(Index))
		{
			VOLUND_ERROR("Container of type (%s) does not contain derived type (%s) with index (%d)!", typeid(T).name(), typeid(D).name(), Index);
		}

		return std::dynamic_pointer_cast<D>(this->_Data[TypeID][Index]);
	}

	template <typename T>
	template <typename D>
	inline bool Container<T>::Contains(uint64_t Index) const
	{
		static uint64_t TypeID = this->GetTypeID<D>();

		return TypeID < this->_Data.size() && Index < this->_Data[TypeID].size();
	}

	template<typename T>
	template <typename D>
	inline const std::vector<Ref<T>>& Container<T>::View() const
	{
		static uint64_t TypeID = this->GetTypeID<D>();

		if (!this->Contains<D>(0))
		{
			VOLUND_ERROR("Container of type (%s) does not contain derived type (%s)!", typeid(T).name(), typeid(D).name());
		}

		return this->_Data[TypeID];
	}

	template <typename T>
	template <typename D>
	inline uint64_t Container<T>::Size() const
	{
		static uint64_t TypeID = this->GetTypeID<D>();

		if (!this->Contains<D>(0))
		{
			VOLUND_ERROR("Container of type (%s) does not contain derived type (%s)!", typeid(T).name(), typeid(D).name());
		}

		return this->_Data[TypeID].size();
	}

	template<typename T>
	template <typename D>
	inline uint64_t Container<T>::GetTypeID() const
	{
		static uint64_t ID = _NewTypeID++;

		return ID;
	}

	template<typename T>
	inline std::vector<std::vector<Ref<T>>>::iterator Container<T>::begin()
	{
		return this->_Data.begin();
	}

	template<typename T>
	inline std::vector<std::vector<Ref<T>>>::iterator Container<T>::end()
	{
		return this->_Data.end();
	}

	template<typename T>
	inline std::vector<std::vector<Ref<T>>>::const_iterator Container<T>::begin() const
	{
		return this->_Data.begin();
	}

	template<typename T>
	inline std::vector<std::vector<Ref<T>>>::const_iterator Container<T>::end() const
	{
		return this->_Data.end();
	}

}
