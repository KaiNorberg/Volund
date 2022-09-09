#pragma once

#include "VMLEntry.h"

namespace Volund
{
	/// <summary>
	/// Volund Markup Language
	/// </summary>
	class VML
	{
	public:

		bool ContainsNode(const std::string& Name) const;

		bool ContainsEntry(const std::string& Name) const;

		VMLEntry const& Get(const std::string& Name) const;

		VMLEntry& Get(const std::string& Name);

		VML& operator[](const std::string& Name);

		void Write(const std::string& FilePath);

		std::string ToString(uint32_t Indentation = 0);

		void PushBack(const std::string& Name, const VML& Node);

		void PushBack(const std::string& Name, const VMLEntry& Entry);

		std::map<std::string, VML>::const_iterator begin() const;
		std::map<std::string, VML>::const_iterator end() const;

		VML() = default;

		VML(const std::string& FilePath);

		VML(std::ifstream& File);

	private:

		void Parse(std::ifstream& File);

		uint32_t GetOccurrencesAtStart(const std::string& String, char Character);

		std::vector<std::string> Split(const std::string& String, char Delimiter);

		std::map<std::string, VML> _Nodes;
		std::map<std::string, VMLEntry> _Entries;
	};
}

