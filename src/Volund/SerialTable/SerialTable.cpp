#include "SerialTable.h"

namespace Volund
{
	void SerialTable::Erase(std::string const& key)
	{
		this->m_table.erase(key);
	}

	void SerialTable::Rename(std::string const& key, std::string const& newKey)
	{
		auto node = this->m_table.extract(key);
		node.key() = newKey;
		this->m_table.insert(std::move(node));
	}

	PrimitiveSerialObject& SerialTable::operator[](std::string const& key)
	{
		return *(this->m_table[key].get());
	}

	const SerialTable::const_iterator SerialTable::begin() const
	{
		return this->m_table.begin();
	}

	const SerialTable::const_iterator SerialTable::end() const
	{
		return this->m_table.end();
	}

	SerialTable::iterator SerialTable::begin()
	{
		return this->m_table.begin();
	}

	SerialTable::iterator SerialTable::end()
	{
		return this->m_table.end();
	}
}
