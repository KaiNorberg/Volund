#pragma once

#include <json/single_include/nlohmann/json.hpp>

#include "Logger/Logger.h"

namespace Volund
{
	class JSON
	{
	public:

		uint64_t Size() const;

		template<typename T>
		T GetAs() const;

		template<typename T>
		bool Contains(T const& Entry);

		template<typename T>
		void AddEntry(std::string const& Name, T const& Entry);

		template<typename T>
		void AddList(std::string const& Name, std::initializer_list<T> const& Entry);

		template<typename T>
		void PushBack(T const& Entry);

		void Save(std::string const& FilePath);

		static JSON Load(std::string const& FilePath);

		template<typename T>
		operator T() const;

		template<typename T>
		bool operator==(T const& Other);

		JSON const operator[](int32_t const& Other) const;

		JSON const operator[](const char* Other) const;

		JSON() = default;

		template<typename T>
		JSON(std::initializer_list<T> List);

		JSON(nlohmann::json const& JSONObject);

	private:

		nlohmann::json _JSONObject;
	};

	template<typename T>
	inline T JSON::GetAs() const
	{
		return this->_JSONObject.get<T>();
	}
	  
	template<typename T>
	inline bool JSON::Contains(T const& Entry)
	{
		return this->_JSONObject.contains(Entry);
	}

	template<>
	inline void JSON::AddEntry(std::string const& Name, JSON const& Entry)
	{
		this->_JSONObject[Name] = Entry._JSONObject;
	}

	template<typename T>
	inline void JSON::AddEntry(std::string const& Name, T const& Entry)
	{
		this->_JSONObject[Name] = Entry;
	}

	template<typename T>
	inline void JSON::AddList(std::string const& Name, std::initializer_list<T> const& Entry)
	{
		this->_JSONObject[Name] = Entry;
	}

	template<>
	inline void JSON::PushBack(JSON const& Entry)
	{
		this->_JSONObject.push_back(Entry._JSONObject);
	}

	template<typename T>
	inline void JSON::PushBack(T const& Entry)
	{
		this->_JSONObject.push_back(Entry);
	}
	
	template<typename T>
	inline JSON::operator T() const
	{
		return this->GetAs<T>();
	}

	template<typename T>
	inline bool JSON::operator==(T const& Other)
	{
		return this->_JSONObject == Other;
	}

	template<typename T>
	inline JSON::JSON(std::initializer_list<T> List)
	{
		this->_JSONObject = nlohmann::json(List);
	}
}