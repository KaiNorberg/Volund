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

	private:

		enum class TokenType
		{
			NONE,
			WORD,
			ENTRY_BEGIN,
			ENTRY_END,
			NODE_BEGIN,
			NODE_END
		};

		struct Token
		{
			TokenType Type = TokenType::NONE;

			std::string Value;
		};

		static void Tokenize(std::vector<Token>* Out, FILE* File);

		void Parse(const std::vector<Token>& Tokens, int& Index);

		uint32_t GetOccurrencesAtStart(const std::string& String, char Character);

		void Split(std::vector<std::string>* Out, const std::string& String, char Delimiter);

		std::map<std::string, VML> _Nodes;
		std::map<std::string, VMLEntry> _Entries;
	};
}

