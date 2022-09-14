#pragma once

namespace Volund
{
	class BaseMaterialValue
	{
	public:

		std::string GetName();

		virtual ~BaseMaterialValue() = default;

	protected:

		std::string _Name;

	};

	template <typename T>
	class MaterialValue : public BaseMaterialValue
	{
	public:

		operator T();

		T GetValue();

		MaterialValue(std::string_view Name, T Value);

	private:

		T _Value;
	};

	template<typename T>
	inline MaterialValue<T>::operator T()
	{
		return this->_Value;
	}

	template<typename T>
	inline T MaterialValue<T>::GetValue()
	{
		return this->_Value;
	}

	template<typename T>
	inline MaterialValue<T>::MaterialValue(std::string_view Name, T Value)
	{
		this->_Name = Name;
		this->_Value = Value;
	}
}
