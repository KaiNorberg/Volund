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

		bool ContainsNode(std::string_view Name) const;

		bool ContainsEntry(std::string_view Name) const;

		VMLEntry const& Get(std::string_view Name) const;

		VMLEntry& Get(std::string_view Name);

		VML& operator[](std::string_view Name);

		void Write(std::string_view Filepath);

		std::string ToString(uint32_t Indentation = 0);

		void PushBack(const std::string& Name, const VML& Node);

		void PushBack(const std::string& Name, const VMLEntry& Entry);

		std::map<std::string, VML>::const_iterator begin() const;
		std::map<std::string, VML>::const_iterator end() const;

		VML() = default;

		VML(std::string_view Filepath);

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

		static void Tokenize(std::vector<Token>* Out, const std::string& File);

		void Parse(const std::vector<Token>& Tokens, int& Index);

		uint32_t GetOccurrencesAtStart(std::string_view String, char Character);

		void Split(std::vector<std::string>* Out, std::string_view String, char Delimiter);

		std::map<std::string, VML> _Nodes;
		std::map<std::string, VMLEntry> _Entries;
	};
}

