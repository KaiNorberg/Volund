#include "PCH/PCH.h"
#include "SerialTable.h"

namespace Volund
{
	void SerialTable::Erase(std::string const& key)
	{
		this->m_Table.erase(key);
	}

	void SerialTable::Rename(std::string const& key, std::string const& newKey)
	{
		auto node = this->m_Table.extract(key);
		node.key() = newKey;
		this->m_Table.insert(std::move(node));
	}

	PrimitiveSerialObject& SerialTable::operator[](std::string const& key)
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
