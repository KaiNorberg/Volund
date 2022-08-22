#include "PCH/PCH.h"

#include "JSON.h"

namespace Volund
{
	JSON LoadJSON(std::string const& FilePath)
	{
		std::ifstream File(FilePath);

		if (!File.is_open())
		{
			VOLUND_CORE_ERROR("Unable to open JSON file (%s)", FilePath);
		}

		return nlohmann::json::parse(File);
	}
}
