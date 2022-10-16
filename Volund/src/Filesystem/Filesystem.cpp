#include "PCH/PCH.h"
#include "Filesystem.h"

namespace Volund
{
	std::unordered_map<std::string, std::string> Filesystem::_Resources =
	{
		{
		":/Simple.vshader",
		#include "Shaders/Simple.vshader"
		}
	};

	std::string Filesystem::Load(const std::string& Filepath)
	{
		static std::string NullString = "";

		if (IsResource(Filepath))
		{
			return _Resources[Filepath];
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
	}

	bool Filesystem::IsResource(const std::string& FileName)
	{
		return _Resources.contains(FileName);
	}

	const std::string& Filesystem::GetResource(const std::string& FileName)
	{
		static std::string NullString = "";

		if (IsResource(FileName))
		{
			return _Resources[FileName];
		}
		else
		{
			return NullString;
		}
	}

	std::unordered_map<std::string, std::string>::const_iterator Filesystem::begin()
	{
		return _Resources.begin();
	}

	std::unordered_map<std::string, std::string>::const_iterator Filesystem::end()
	{
		return _Resources.end();
	}
}