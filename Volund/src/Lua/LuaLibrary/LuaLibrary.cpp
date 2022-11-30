#include "PCH/PCH.h"
#include "LuaLibrary.h"

namespace Volund
{
	std::vector<LibEntry>::const_iterator LuaLibrary::begin() const
	{
		return this->_Functions.begin();
	}

	std::vector<LibEntry>::const_iterator LuaLibrary::end() const
	{
		return this->_Functions.end();
	}

	LuaLibrary::LuaLibrary(std::initializer_list<LibEntry> List) : _Functions(List)
	{

	}
}