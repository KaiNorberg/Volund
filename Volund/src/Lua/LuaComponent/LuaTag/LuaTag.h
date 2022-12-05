#pragma once

#include "Lua/LuaComponent/LuaComponent.h"
#include "Lua/LuaComponent/LuaComponents.h"

#include "Scene/Component/Tag/Tag.h"

namespace Volund
{
	struct LuaTag
	{
	public:

		std::string Get();
		void Set(std::string String);

		LuaTag(Ref<Tag> Tag);

	private:

		Ref<Tag> _Tag;
	};
}