#include "PCH/PCH.h"
#include "VML.h"

#include "Time/Time.h"

namespace Volund
{
	bool VML::ContainsNode(const std::string& Name) const
	{
		return this->_Nodes.contains(Name);
	}

	bool VML::ContainsEntry(const std::string& Name) const
	{
		return this->_Entries.contains(Name);
	}

	VMLEntry const& VML::Get(const std::string& Name) const
	{
		if (this->ContainsEntry(Name))
		{
			return this->_Entries.at(Name);
		}
		else
		{
			VOLUND_ERROR("Unable to find VML entry (%s)!", Name.c_str());
		}
	
		return this->_Entries.at("");
	}

	VMLEntry& VML::Get(const std::string& Name)
	{
		if (this->ContainsEntry(Name))
		{
			return this->_Entries[Name];
		}
		else
		{
			VOLUND_ERROR("Unable to find VML entry (%s)!", Name.c_str());
		}	

		return this->_Entries.at("");
	}

	VML& VML::operator[](const std::string& Name)
	{
		if (this->ContainsNode(Name))
		{
			return this->_Nodes[Name];
		}
		else
		{
			VOLUND_ERROR("Unable to find VML node (%s)!", Name.c_str());
		}

		return this->_Nodes.at("");
	}

	void VML::Write(const std::string& FilePath)
	{
		std::ofstream File(FilePath, std::ofstream::out | std::ofstream::trunc);

		if (File.fail())
		{
			VOLUND_ERROR("Unable to write to VML file (%s)!", FilePath.c_str());
		}

		File << this->ToString();
	}

	std::string VML::ToString(uint32_t Indentation)
	{
		std::string IndentationString(Indentation, '\t');

		std::string Result;
		for (auto& [EntryName, Entry] : this->_Entries)
		{
			Result += IndentationString + EntryName + " [ ";

			for (uint32_t i = 0; i < Entry.Size(); i++)
			{
				Result += Entry[i].GetAs<std::string>() + ' ';
			}

			Result += "]\n";
		}

		for (auto& [NodeName, Node] : this->_Nodes)
		{
			Result += IndentationString + NodeName + '\n' + IndentationString + "{\n";
			Result += Node.ToString(Indentation + 1) + IndentationString + "}\n";
		}

		return Result;
	}

	void VML::PushBack(const std::string& Name, const VML& Node)
	{
		this->_Nodes[Name] = Node;
	}

	void VML::PushBack(const std::string& Name, const VMLEntry& Entry)
	{
		this->_Entries[Name] = Entry;
	}

	std::map<std::string, VML>::const_iterator VML::begin() const
	{
		return this->_Nodes.begin();
	}

	std::map<std::string, VML>::const_iterator VML::end() const
	{
		return this->_Nodes.end();
	}

	void VML::Tokenize(std::vector<Token>* Out, FILE* File)
	{
		while (true)
		{
			char TokenString[128];
			int RET = fscanf(File, "%128s", TokenString);
			if (RET == EOF || RET == NULL)
			{
				return;
			}

			Token NewToken;
			NewToken.Value = TokenString;

			if (strlen(TokenString) == 1)
			{
				switch (TokenString[0])
				{
				case '[':
				{
					NewToken.Type = TokenType::ENTRY_BEGIN;
				}
				break;
				case ']':
				{
					NewToken.Type = TokenType::ENTRY_END;
				}
				break;
				case '{':
				{
					NewToken.Type = TokenType::NODE_BEGIN;
				}
				break;
				case '}':
				{
					NewToken.Type = TokenType::NODE_END;
				}
				break;
				default:
				{
					NewToken.Type = TokenType::WORD;
				}
				}
			}
			else
			{
				NewToken.Type = TokenType::WORD;
			}

			Out->push_back(NewToken);
		}
	}

	void VML::Parse(const std::vector<Token>& Tokens, int& Index)
	{
		std::string LastIdentifier;

		bool InEntry = false;
		VMLEntry NewEntry;

		for (; Index < Tokens.size(); Index++)
		{
			switch (Tokens[Index].Type)
			{
			case TokenType::ENTRY_BEGIN:
			{
				if (InEntry)
				{
					VOLUND_ERROR("Unable to read VLM file, invalid token (%s)!", Tokens[Index].Value.c_str());
				}

				InEntry = true;
			}
			break;
			case TokenType::ENTRY_END:
			{
				if (!InEntry)
				{
					VOLUND_ERROR("Unable to read VLM file, invalid token (%s)!", Tokens[Index].Value.c_str());
				}

				this->PushBack(LastIdentifier, NewEntry);
				
				NewEntry = VMLEntry();
				LastIdentifier.clear();
				InEntry = false;
			}
			break;
			case TokenType::NODE_BEGIN:
			{
				Index++;

				VML NewNode;
				NewNode.Parse(Tokens, Index);

				this->PushBack(LastIdentifier, NewNode);
				LastIdentifier.clear();		
			}
			break;
			case TokenType::NODE_END:
			{
				return;
			}
			break;
			case TokenType::WORD:
			{
				if (InEntry)
				{
					NewEntry.PushBack(Tokens[Index].Value);
				}
				else if (LastIdentifier.empty())
				{
					LastIdentifier = Tokens[Index].Value;
				}
				else
				{
					VOLUND_ERROR("Unable to read VLM file, invalid token (%s)!", Tokens[Index].Value.c_str());
				}
			}
			break;
			}
		}
	}

	uint32_t VML::GetOccurrencesAtStart(const std::string& String, char Character)
	{
		uint32_t Occurrences = 0;
		for (uint64_t i = 0; i < String.size(); i++)
		{
			if (String[i] == Character)
			{
				Occurrences++;
			}
			else
			{
				break;
			}
		}

		return Occurrences;
	}

	void VML::Split(std::vector<std::string>* Out, const std::string& String, char Delimiter)
	{
		Out->reserve(16);

		int64_t OldIndex = 0;
		for (int64_t i = 0; i < (int64_t)String.size(); i++)
		{
			if (String[i] == Delimiter)
			{
				Out->push_back(String.substr(OldIndex, i - OldIndex));
				OldIndex = i + 1;
			}
		}
		Out->push_back(String.substr(OldIndex, String.size()));
	}

	VML::VML(const std::string& FilePath)
	{
		VOLUND_INFO("Loading VML file (%s)...", FilePath.c_str());

		FILE* File = fopen(FilePath.c_str(), "r");

		VOLUND_ASSERT(File, "Unable to open VML file (%s)!", FilePath.c_str());

		std::vector<Token> Tokens;
		Tokenize(&Tokens, File);

		int Index = 0;
		this->Parse(Tokens, Index);

		fclose(File);
	}
}