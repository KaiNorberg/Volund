#pragma once

#define VOLUND_CONFIG_JSON "Config.json"

#define VOLUND_ASSERT(Check, ...) if (!Check) { VOLUND_ERROR(__VA_ARGS__); }

namespace Volund
{
	template<typename T>
	using Scope = std::unique_ptr<T>;

	template<typename T>
	using Ref = std::shared_ptr<T>;
}