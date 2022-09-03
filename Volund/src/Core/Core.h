#pragma once

#define VOLUND_CONFIG_JSON "Config.json"

#define VOLUND_ASSERT(Check, ...) if (!(bool)(Check)) { VOLUND_ERROR(__VA_ARGS__); }

namespace Volund
{
	/// <summary>
	/// Unique ptr
	/// </summary>
	template<typename T>
	using Scope = std::unique_ptr<T>;

	/// <summary>
	/// Shared ptr
	/// </summary>
	template<typename T>
	using Ref = std::shared_ptr<T>;
}