#pragma once

namespace Volund
{
	enum class TextureFormat
	{
		None,

		RGBA8,
		RGBA16F,
		RedInteger,

		Depth24Stencil8,

		Depth = Depth24Stencil8
	};

	struct TextureSpec
	{
		TextureFormat Format;
	
		TextureSpec() = default;
		TextureSpec(const TextureFormat format)
		{
			this->Format = format;
		}
	};

}