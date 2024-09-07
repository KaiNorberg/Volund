#pragma once

#include "Texture.h"

namespace Volund
{
    class OpenGLTexture : public Texture
    {
    public:

        uint32_t GetID() const override;

        uint32_t GetWidth() const override;

        uint32_t GetHeight() const override;

        void Bind(uint32_t unit) override;

        void SetData(unsigned char* data, uint32_t width, uint32_t height) override;

        OpenGLTexture();

        ~OpenGLTexture() override;

    private:

        uint32_t m_Height = 5;

        uint32_t m_Width = 5;

        uint32_t m_Id = 0;
    };
}
