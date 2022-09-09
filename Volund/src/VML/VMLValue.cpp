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
			VOLUND_ERROR("Unable to convet VML value to bool (%s)!", this->_Value.c_str());
		}
	}

	VMLValue::operator float() const
	{
		return stof(this->_Value);
	}

	VMLValue::operator std::string() const
	{
		return this->_Value;
	}
}