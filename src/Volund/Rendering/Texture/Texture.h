#pragma once

namespace Volund
{
    class Texture
    {
    public:

        virtual uint32_t GetID() const = 0;

        virtual uint32_t GetWidth() const = 0;

        virtual uint32_t GetHeight() const = 0;

        virtual void Bind(uint32_t unit = 0) = 0;

        virtual void SetData(unsigned char* data, uint32_t width, uint32_t height) = 0;

        static std::shared_ptr<Texture> Create();

        static std::shared_ptr<Texture> Create(const std::string& filepath);

        static std::shared_ptr<Texture> Create(unsigned char* data, uint32_t width, uint32_t height);

        virtual ~Texture() = default;
    };
}
