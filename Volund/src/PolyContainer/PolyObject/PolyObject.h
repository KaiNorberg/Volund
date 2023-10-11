#pragma once

namespace Volund
{
	class PrimitivePolyObject
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

		virtual uint64_t GetTypeHash() const = 0;

	private:

	};

	template<typename T>
	class PolyObject : public PrimitivePolyObject
	{
	public:

		void Set(const T& data);

		T& Get();

		const T& Get() const;

		uint64_t GetTypeHash() const override;

		PolyObject(const T& data);

	private:

		T m_Data;
	};

	template<typename T>
	inline bool PrimitivePolyObject::Is()
	{
		return this->GetTypeHash() == typeid(T).hash_code();
	}

	template<typename T>
	inline void PrimitivePolyObject::operator=(T data)
	{
		if (!this->Is<T>())
		{
			VOLUND_ERROR("Attempt to set PrimitivePolyObject with incorrect type!");
		}

		((PolyObject<T>*)this)->Set(data);
	}

	template<typename T>
	PrimitivePolyObject::operator T()
	{
		return this->As<T>();
	}

	template<typename T>
	inline T PrimitivePolyObject::As()
	{
		if (!this->Is<T>())
		{
			VOLUND_ERROR("Wrong type requested from PrimitivePolyObject!");
		}

		return ((PolyObject<T>*)this)->Get();
	}

	template<typename T>
	inline const T& PolyObject<T>::Get() const
	{
		return this->m_Data;
	}

	template<typename T>
	inline T& PolyObject<T>::Get()
	{
		return this->m_Data;
	}

	template<typename T>
	inline void PolyObject<T>::Set(const T& data)
	{
		this->m_Data = data;
	}

	template<typename T>
	inline uint64_t PolyObject<T>::GetTypeHash() const
	{
		return typeid(T).hash_code();
	}

	template<typename T>
	inline PolyObject<T>::PolyObject(const T& data)
	{
		this->m_Data = data;
	}
}
