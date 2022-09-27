#pragma once

namespace Volund
{
	enum class TextureFormat
	{
		NONE,

		RGBA8,

		DEPTH24STENCIL8,

		DEPTH = DEPTH24STENCIL8
	};

	struct TextureSpec
	{
		TextureFormat Format;
	
		TextureSpec() = default;
		TextureSpec(TextureFormat Format)
		{
			this->Format = Format;
		}
	};

}