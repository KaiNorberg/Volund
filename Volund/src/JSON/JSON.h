#pragma once

namespace Volund
{
	using JSON = nlohmann::json;

	 JSON LoadJSON(std::string const& FilePath);
}
