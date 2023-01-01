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

		template<typename D>
		void PushBack(Ref<D> Entry);

		template<typename D>
		void PushBack(D* Entry);

		template<typename D>
		void Erase(uint64_t Index = 0);

		template<typename D>
		Ref<D> Get(uint64_t Index = 0);

		template<typename D>
		bool Contains();

		template<typename D>
		uint64_t Size();

		template<typename D>
		const std::vector<Ref<T>>& View();

		std::unordered_map<uint64_t, std::vector<Ref<T>>>::iterator begin();
		std::unordered_map<uint64_t, std::vector<Ref<T>>>::iterator end();

		std::unordered_map<uint64_t, std::vector<Ref<T>>>::const_iterator begin() const;
		std::unordered_map<uint64_t, std::vector<Ref<T>>>::const_iterator end() const;

	private:

		std::unordered_map<uint64_t, std::vector<Ref<T>>> _Data;
	};

	template<typename T>
	template<typename D>
	inline void Container<T>::PushBack(Ref<D> Entry)
	{
		static uint64_t TypeID = typeid(D).hash_code();

		this->_Data[TypeID].push_back(Entry);
	}

	template<typename T>
	template<typename D>
	inline void Container<T>::PushBack(D* Entry)
	{
		static uint64_t TypeID = typeid(D).hash_code();

		this->_Data[TypeID].push_back(Ref<D>(Entry));
	}

	template<typename T>
	template<typename D>
	inline void Container<T>::Erase(uint64_t Index)
	{
		static uint64_t TypeID = typeid(D).hash_code();

		if (this->_Data.contains(TypeID) && this->_Data[TypeID].size() > Index)
		{
			this->_Data[TypeID].erase(this->_Data[TypeID].begin() + Index);
		}
	}

	template<typename T>
	template<typename D>
	inline Ref<D> Container<T>::Get(uint64_t Index)
	{
		static uint64_t TypeID = typeid(D).hash_code();

		return std::dynamic_pointer_cast<D>(this->_Data[TypeID][Index]);
	}

	template<typename T>
	template<typename D>
	inline bool Container<T>::Contains()
	{
		static uint64_t TypeID = typeid(D).hash_code();

		return this->_Data.contains(TypeID);
	}

	template<typename T>
	template<typename D>
	inline uint64_t Container<T>::Size()
	{
		static uint64_t TypeID = typeid(D).hash_code();

		return this->_Data[TypeID].size();
	}

	template<typename T>
	template<typename D>
	inline const std::vector<Ref<T>>& Container<T>::View()
	{
		static uint64_t TypeID = typeid(D).hash_code();

		return this->_Data[TypeID];
	}

	template<typename T>
	inline std::unordered_map<uint64_t, std::vector<Ref<T>>>::iterator Container<T>::begin()
	{
		return this->_Data.begin();
	}

	template<typename T>
	inline std::unordered_map<uint64_t, std::vector<Ref<T>>>::iterator Container<T>::end()
	{
		return this->_Data.end();
	}

	template<typename T>
	inline std::unordered_map<uint64_t, std::vector<Ref<T>>>::const_iterator Container<T>::begin() const
	{
		return this->_Data.begin();
	}

	template<typename T>
	inline std::unordered_map<uint64_t, std::vector<Ref<T>>>::const_iterator Container<T>::end() const
	{
		return this->_Data.end();
	}
}
