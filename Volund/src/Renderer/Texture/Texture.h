#pragma once

namespace Volund
{
	class Texture
	{
	public:

		std::string GetFilepath();

		uint32_t GetID() const;

		uint32_t GetWidth() const;

		uint32_t GetHeight() const;

		virtual void Bind(uint32_t unit = 0) = 0;

		static Ref<Texture> Create(const std::string& filepath);

		virtual ~Texture() = default;

	protected:

		uint32_t m_Height = 0;

		uint32_t m_Width = 0;

		std::string m_Filepath;

		uint32_t m_ID = 0;
	};
}
