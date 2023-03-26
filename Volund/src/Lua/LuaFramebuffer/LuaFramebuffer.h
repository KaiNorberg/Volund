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

		void Resize(LuaVec2 newSize);

		LuaVec2 GetSize();

		LuaFramebuffer(const LuaVec2& size);

		LuaFramebuffer(Ref<Framebuffer> framebuffer);

	private:

		Ref<Framebuffer> m_Framebuffer;
	};
}