#pragma once

namespace Volund
{
	class Texture
	{
	public:

		uint32_t GetWidth();

		uint32_t GetHeight();

		virtual void Bind(uint32_t Unit = 0) = 0;
		
		virtual ~Texture() = default;

	protected:

		uint32_t _Height = 0;

		uint32_t _Width = 0;
	};

	class Texture2D : public Texture
	{
	public:

		static Ref<Texture2D> Create(std::string const& FilePath);

	protected:
	};
}
