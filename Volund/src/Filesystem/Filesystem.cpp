#include "PCH/PCH.h"
#include "Filesystem.h"

namespace Volund
{
	void Resource::CreateSubDir(const std::string& SubDir)
	{
		this->_Children[SubDir] = Resource(SubDir);
	}

	void Resource::CreateFile(const std::string& FileName, const std::string& FileData)
	{
		this->_Children[FileName] = Resource(FileName, FileData);
	}

	const std::string& Resource::GetData() const
	{
		return this->_Data;
	}

	bool Resource::Contains(const std::string& Name) const
	{
		return this->_Children.contains(Name);
	}

	std::string Resource::Extension() const
	{
		if (this->_Name.contains('.'))
		{
			return this->_Name.substr(this->_Name.find('.'));
		}
		else
		{
			return "";
		}
	}

	bool Resource::IsDirectory() const
	{
		return this->Extension() == "";
	}

	Resource& Resource::operator[](const std::string& Name)
	{
		static Resource NULL_RESOURCE = Resource("");

		if (this->_Children.contains(Name))
		{
			return this->_Children[Name];
		}
		else
		{
			return NULL_RESOURCE;
		}
	}

	const std::unordered_map<std::string, Resource>::const_iterator Resource::begin() const
	{
		return this->_Children.begin();
	}

	const std::unordered_map<std::string, Resource>::const_iterator Resource::end() const
	{
		return this->_Children.end();
	}

	Resource::Resource(const std::string& Name, const std::string& Data)
	{
		this->_Name = Name;
		this->_Data = Data;
	}

	std::string Filesystem::Load(const std::string& Filepath)
	{
		static Filesystem SingleTon;

		if (Filepath.starts_with(":/"))
		{
			std::string ResourcePath = Filepath.substr(2);

			std::stringstream Stream(ResourcePath);
			std::string Word;
			Resource* PrevResource = &_GrandfatherResource;
			while (std::getline(Stream, Word, '/'))
			{
				if (PrevResource->Contains(Word))
				{
					PrevResource = &((*PrevResource)[Word]);
				}
				else
				{
					VOLUND_ERROR("Invalid Resource (%s)", Word.c_str());
				}
			}

			return PrevResource->GetData();
		}
		else
		{
			std::ifstream File(Filepath);
			VOLUND_ASSERT(File, "Unable to load file (%s).", Filepath.c_str());
			std::string Line;
			std::string Output;
			while (std::getline(File, Line))
			{
				Output += Line + '\n';
			}
			return Output;
		}
		
		return "";
	}

	Resource* Filesystem::GetGrandFatherResource()
	{
		return &_GrandfatherResource;
	}

	Filesystem::Filesystem()
	{
		_GrandfatherResource.CreateSubDir("Shaders");
		_GrandfatherResource["Shaders"].CreateFile(
			"Simple.vshader",
			#include "Shaders/Simple.vshader"
		);
	}		
}