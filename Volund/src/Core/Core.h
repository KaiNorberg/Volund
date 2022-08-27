#pragma once

#define VOLUND_CONFIG_JSON "Config.json"

namespace Volund
{
	template<typename T>
	using Scope = std::unique_ptr<T>;

	template<typename T>
	using Ref = std::shared_ptr<T>;
}