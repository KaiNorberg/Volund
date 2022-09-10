#pragma once

namespace Volund
{
	class VMLValue
	{
	public:

		operator int() const;

		operator bool() const;

		operator float() const;

		operator std::string() const;

		template <typename T>
		T GetAs() const;

		const std::string& String() const;

		template <typename T>
		VMLValue(const T Value);

	private:

		std::string _Value;
	};

	template <typename T>
	inline T VMLValue::GetAs() const
	{
		return this->operator T();
	}

	template <>
	inline VMLValue::VMLValue(const std::string Value)
	{
		this->_Value = Value;
	}

	template <>
	inline VMLValue::VMLValue(const char* Value)
	{
		this->_Value = Value;
	}

	template <typename T>
	inline VMLValue::VMLValue(const T Value)
	{
		this->_Value = std::to_string(Value);
	}
}

