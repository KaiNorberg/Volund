#include "PCH/PCH.h"
#include "VMLEntry.h"

namespace Volund
{
	std::string_view VMLEntry::String(uint32_t Index) const
	{
		return this->_Values[Index].String();
	}

	void VMLEntry::PushBack(std::string_view Value)
	{
		this->_Values.push_back(Value);
	}

	uint32_t VMLEntry::Size() const
	{
		return (uint32_t)this->_Values.size();
	}

	VMLValue& VMLEntry::operator[](uint32_t Index)
	{
		if (Index < this->_Values.size())
		{
			return this->_Values[Index];
		}
		else
		{
			VOLUND_ERROR("Index exceeds boundary of VML entry (%d)!", Index);
		}

		return this->_Values[0];
	}
}