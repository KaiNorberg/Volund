#pragma once

namespace Volund
{
	class Texture
	{
	public:

		std::string GetFilepath();

		uint32_t GetWidth() const;

		uint32_t GetHeight() const;

		virtual void Bind(uint32_t Unit = 0) = 0;

		static Ref<Texture> Create(std::string_view Filepath);

		virtual ~Texture() = default;

	protected:

		uint32_t _Height = 0;

		uint32_t _Width = 0;

		std::string _Filepath;
	};
}
