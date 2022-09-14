#pragma once

#include "VMLValue.h"

namespace Volund
{
	class VMLEntry
	{
	public:

		template <typename T>
		operator T() const;

		std::string_view String(uint32_t Index = 0) const;

		template <typename T>
		T GetAs() const;

		void PushBack(std::string_view Value);

		uint32_t Size() const;

		VMLValue& operator[](uint32_t Index);

		VMLEntry() = default;

		template <typename T>
		VMLEntry(const std::initializer_list<T>& Values);

		template <typename T>
		VMLEntry(const std::vector<T>& Values);

		template <typename T>
		VMLEntry(const T& Value);

	private:

		std::vector<VMLValue> _Values;
	};

	template<typename T> 
	inline VMLEntry::operator T() const
	{
		return this->_Values[0];
	}

	template<typename T>
	inline T VMLEntry::GetAs() const
	{
		return this->_Values[0];
	}

	template<typename T>
	inline VMLEntry::VMLEntry(const std::initializer_list<T>& Values)
	{
		this->_Values.reserve(Values.size());
		for (auto& Value : Values)
		{
			this->_Values.emplace_back(Value);
		}
	}

	template<typename T>
	inline VMLEntry::VMLEntry(const std::vector<T>& Values)
	{
		this->_Values.reserve(Values.size());
		for (auto& Value : Values)
		{
			this->_Values.emplace_back(Value);
		}
	}

	template <typename T>
	inline VMLEntry::VMLEntry(const T& Value)
	{
		this->_Values.emplace_back(Value);
	}
}

