
#include "Component/Tag.h"
#include "Lua/LuaAPI.h"

namespace Volund
{
	Tag::Tag(std::string const& string)
	{
		this->string = string;
	}

    VOLUND_USERTYPE_COMPONENT_REGISTER(Tag,
    [](LuaState* state){
        state->NewUsertype<Tag>("Tag", 
            sol::constructors<>(),
            "string", &Tag::string
        );
    }, std::string const&);
}