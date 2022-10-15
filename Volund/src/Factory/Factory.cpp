#include "PCH/PCH.h"
#include "Factory.h"

namespace Volund
{
	std::unordered_map<std::string, const char*> Factory::_Resources =
	{
		{
		":/Simple.vshader",
		#include "Shaders/Simple.vshader"
		}
	};

	bool Factory::IsResource(const std::string& FileName)
	{
		return _Resources.contains(FileName);
	}

	const char* Factory::GetResource(const std::string& FileName)
	{
		return _Resources[FileName];
	}

	std::unordered_map<std::string, const char*>::const_iterator Factory::begin() const
	{
		return this->_Resources.begin();
	}

	std::unordered_map<std::string, const char*>::const_iterator Factory::end() const
	{
		return this->_Resources.end();
	}
}