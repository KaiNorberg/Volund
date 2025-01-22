#pragma once

namespace Volund
{
    enum class TextureFormat
    {
        None,
        RGBA8,
        RGBA16F,
        RGBA32UI,
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