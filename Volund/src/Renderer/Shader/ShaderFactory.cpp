#include "PCH/PCH.h"
#include "ShaderFactory.h"

namespace Volund
{
	std::unordered_map<std::string, const char*> ShaderFactory::_Shaders =		
	{
		{
		":/Simple.vshader",
		#include "Shaders/Simple.vshader"
		}
	};

	bool ShaderFactory::IsResource(const std::string& FileName)
	{
		return _Shaders.contains(FileName);
	}

	const char* ShaderFactory::GetResource(const std::string& FileName)
	{
		return _Shaders[FileName];
	}
}