#include "PCH/PCH.h"
#include "VMLValue.h"

namespace Volund
{
	VMLValue::operator int() const
	{
		return stoi(this->_Value);
	}

	VMLValue::operator bool() const
	{
		if (_Value == "false")
		{
			return false;
		}
		else if (_Value == "true")
		{
			return true;
		}
		else
		{
			return (bool)stoi(this->_Value);
		}
	}

	VMLValue::operator float() const
	{
		return stof(this->_Value);
	}

	VMLValue::operator double() const
	{
		return stod(this->_Value);
	}

	VMLValue::operator std::string() const
	{
		return this->_Value;
	}

	VMLValue::operator std::string_view() const
	{
		return this->_Value;
	}

	std::string_view VMLValue::String() const
	{
		return this->_Value;
	}
}