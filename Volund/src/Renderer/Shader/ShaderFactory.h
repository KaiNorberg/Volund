#pragma once

namespace Volund
{
	class ShaderFactory
	{
	public:

		static bool IsResource(const std::string& FileName);

		static const char* GetResource(const std::string& FileName);

	private:

		static std::unordered_map<std::string, const char*> _Shaders;

	};
}