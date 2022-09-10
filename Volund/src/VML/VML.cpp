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
			Result += IndentationString + EntryName + '=';

			for (uint32_t i = 0; i < Entry.Size(); i++)
			{
				Result += Entry[i];
				if (i != Entry.Size() - 1)
				{
					Result += ',';
				}
			}

			Result += '\n';
		}

		for (auto& [NodeName, Node] : this->_Nodes)
		{
			Result += IndentationString + NodeName + ":\n";
			Result += Node.ToString(Indentation + 1);
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

	void VML::Parse(std::ifstream& File)
	{
		std::streampos PrevStreamPos;

		std::string Line;
		uint32_t TabCount = 0;

		if (std::getline(File, Line))
		{
			TabCount = this->GetOccurrencesAtStart(Line, '\t');
		}
		else
		{
			return;
		}

		do
		{
			uint32_t NewTabCount = this->GetOccurrencesAtStart(Line, '\t');

			if (NewTabCount != TabCount)
			{
				if (NewTabCount < TabCount)
				{
					File.seekg(PrevStreamPos);

					return;
				}
				else
				{
					VOLUND_ERROR("Invalid indentation found in VML file!");
				}
			}

			if (Line.back() == ':') //New node
			{
				std::string NodeName = Line.substr(TabCount, Line.size() - TabCount - 1);

				if (this->ContainsNode(NodeName))
				{
					VOLUND_ERROR("Duplicate node in VML file found (%s)!", NodeName.c_str());
				}

				this->_Nodes.emplace(NodeName, File);
			}
			else
			{
				uint64_t EqualPos = Line.find_first_of('=');
				if (EqualPos != std::string::npos)
				{
					std::string EntryName = Line.substr(TabCount, EqualPos - TabCount);
					std::string EntryValue = Line.substr(EqualPos + 1, Line.size() - 1);

					if (!EntryValue.empty())
					{ 
						std::vector<std::string> Values;
						this->Split(&Values, EntryValue, ',');

						if (this->ContainsEntry(EntryName))
						{
							VOLUND_ERROR("Duplicate entry in VML file found (%s)!", EntryName.c_str());
						}

						this->_Entries.emplace(EntryName, Values);
					}
					else
					{
						this->PushBack(EntryName, VMLEntry());
					}
				}
				else
				{
					VOLUND_ERROR("Unable to read VML file!");
				}
			}

			PrevStreamPos = File.tellg();

		} while (std::getline(File, Line));
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

		std::ifstream File(FilePath);

		if (File.fail())
		{
			VOLUND_ERROR("Unable to open VML file (%s)!", FilePath.c_str());
		}

		this->Parse(File);
	}

	VML::VML(std::ifstream& File)
	{
		this->Parse(File);
	}
}