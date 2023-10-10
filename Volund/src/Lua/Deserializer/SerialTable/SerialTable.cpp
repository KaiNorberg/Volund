#include "PCH/PCH.h"
#include "SerialTable.h"

namespace Volund
{
	PrimitiveSerialObject& SerialTable::operator[](const std::string& key)
	{
		return *(this->m_Table[key].get());
	}

	const SerialTable::const_iterator SerialTable::begin() const
	{
		return this->m_Table.begin();
	}

	const SerialTable::const_iterator SerialTable::end() const
	{
		return this->m_Table.end();
	}

	SerialTable::iterator SerialTable::begin()
	{
		return this->m_Table.begin();
	}

	SerialTable::iterator SerialTable::end()
	{
		return this->m_Table.end();
	}
}