#pragma once

#include "../Texture.h"

namespace Volund
{
    class OpenGLTexture : public Texture
    {
    public:
        std::string GetFilepath() const override;
        uint32_t GetID() const override;
        uint32_t GetWidth() const override;
        uint32_t GetHeight() const override;
        void Bind(uint32_t unit) override;
        void SetData(unsigned char* data, uint32_t width, uint32_t height) override;
        OpenGLTexture(std::string const& filepath);
        OpenGLTexture(unsigned char* data, uint32_t width, uint32_t height);
        ~OpenGLTexture() override;
    private:
        std::string m_filepath = "";
        uint32_t m_height = 5;
        uint32_t m_width = 5;
        uint32_t m_id = 0;
    };
}