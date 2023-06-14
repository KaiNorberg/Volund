#pragma once

namespace Volund
{
	class Texture
	{
	public:

		uint32_t GetID() const;

		uint32_t GetWidth() const;

		uint32_t GetHeight() const;

		virtual void Bind(uint32_t unit = 0) = 0;

		virtual void SetData(unsigned char* data, uint32_t width, uint32_t height) = 0;

		static Ref<Texture> Create();

		static Ref<Texture> Create(const std::string& filepath);

		static Ref<Texture> Create(unsigned char* data, uint32_t width, uint32_t height);

		static Ref<Texture> CreateAsync(const std::string& filepath);

		virtual ~Texture() = default;

	protected:

		uint32_t m_Height = 5;

		uint32_t m_Width = 5;

		uint32_t m_ID = 0;
	};
}
