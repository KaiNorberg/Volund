#include "PCH/PCH.h"

#include "JSON.h"

namespace Volund
{
	JSON LoadJSON(std::string const& FilePath)
	{
		std::ifstream File(FilePath);

		if (!File.is_open())
		{
			Console::LogError("Unable to open JSON file (", FilePath, ")");
		}

		return nlohmann::json::parse(File);
	}
}
