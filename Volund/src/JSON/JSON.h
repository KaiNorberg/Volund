#pragma once

namespace Volund
{
	using JSON = nlohmann::json;

	VOLUND_API JSON LoadJSON(std::string const& FilePath);
}
