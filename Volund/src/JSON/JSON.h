#pragma once

#include <json/single_include/nlohmann/json.hpp>

namespace Volund
{
	class JSON
	{
	public:
		uint64_t Size() const;

		template <typename T>
		T GetAs() const;

		template <typename T>
		bool Contains(const T& Entry);

		template <typename T>
		void AddEntry(const std::string& Name, const T& Entry);

		template <typename T>
		void AddList(const std::string& Name, const std::initializer_list<T>& Entry);

		template <typename T>
		void PushBack(const T& Entry);

		void Save(const std::string& FilePath) const;

		static JSON Load(const std::string& FilePath);

		template <typename T>
		operator T() const;

		template <typename T>
		bool operator==(const T& Other);

		const JSON operator[](const int32_t& Other) const;

		const JSON operator[](const char* Other) const;

		JSON() = default;

		template <typename T>
		JSON(std::initializer_list<T> List);

		JSON(const nlohmann::json& JSONObject);

	private:
		nlohmann::json _JSONObject;
	};

	template <typename T>
	T JSON::GetAs() const
	{
		return this->_JSONObject.get<T>();
	}

	template <typename T>
	bool JSON::Contains(const T& Entry)
	{
		return this->_JSONObject.contains(Entry);
	}

	template <>
	inline void JSON::AddEntry(const std::string& Name, const JSON& Entry)
	{
		this->_JSONObject[Name] = Entry._JSONObject;
	}

	template <typename T>
	void JSON::AddEntry(const std::string& Name, const T& Entry)
	{
		this->_JSONObject[Name] = Entry;
	}

	template <typename T>
	void JSON::AddList(const std::string& Name, const std::initializer_list<T>& Entry)
	{
		this->_JSONObject[Name] = Entry;
	}

	template <>
	inline void JSON::PushBack(const JSON& Entry)
	{
		this->_JSONObject.push_back(Entry._JSONObject);
	}

	template <typename T>
	void JSON::PushBack(const T& Entry)
	{
		this->_JSONObject.push_back(Entry);
	}

	template <typename T>
	JSON::operator T() const
	{
		return this->GetAs<T>();
	}

	template <typename T>
	bool JSON::operator==(const T& Other)
	{
		return this->_JSONObject == Other;
	}

	template <typename T>
	JSON::JSON(std::initializer_list<T> List)
	{
		this->_JSONObject = nlohmann::json(List);
	}
}
