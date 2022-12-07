#pragma once

#include "Core/Lua/LuaComponent/LuaComponent.h"
#include "Core/Lua/LuaComponent/LuaComponents.h"

#include "Core/Scene/Component/Tag/Tag.h"

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