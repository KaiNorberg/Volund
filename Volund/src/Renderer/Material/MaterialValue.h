#pragma once

namespace Volund
{
	class BaseMaterialValue
	{
	public:

		std::string GetName();

		virtual ~BaseMaterialValue() = default;

	protected:

		std::string m_Name;

	};

	template <typename T>
	class MaterialValue : public BaseMaterialValue
	{
	public:

		operator T();

		T GetValue();

		MaterialValue(std::string_view name, T value);

	private:

		T m_Value;
	};

	template<typename T>
	inline MaterialValue<T>::operator T()
	{
		return this->m_Value;
	}

	template<typename T>
	inline T MaterialValue<T>::GetValue()
	{
		return this->m_Value;
	}

	template<typename T>
	inline MaterialValue<T>::MaterialValue(std::string_view name, T value)
	{
		this->m_Name = name;
		this->m_Value = value;
	}
}
