#include "PCH/PCH.h"
#include "LuaTag.h"

#include "Scene/Component/Components.h"

namespace Volund
{
	std::string LuaTag::Get()
	{
		return this->_Tag->String;
	}

	void LuaTag::Set(std::string String)
	{
		this->_Tag->String = String;
	}

	LuaTag::LuaTag(Ref<Tag> Tag)
	{
		this->_Tag = Tag;
	}
}