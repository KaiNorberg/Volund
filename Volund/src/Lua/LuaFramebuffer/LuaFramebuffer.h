#pragma once

#include "Renderer/Framebuffer/Framebuffer.h"

#include "Lua/LuaVec/LuaVec.h"

namespace Volund
{
	struct LuaFramebuffer
	{
	public:

		int Padding = NULL;

		Ref<Framebuffer> Get();

		void Resize(LuaVec2 NewSize);

		LuaVec2 GetSize();

		LuaFramebuffer(const LuaVec2& Size);

		LuaFramebuffer(Ref<Framebuffer> RawFramebuffer);

	private:

		Ref<Framebuffer> _Framebuffer;
	};
}