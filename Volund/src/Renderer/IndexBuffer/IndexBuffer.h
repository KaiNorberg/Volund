#pragma once

namespace Volund
{
	class Indexbuffer
	{
	public:
		virtual void Bind() = 0;

		virtual void Unbind() = 0;

		uint32_t GetCount() const;

		static Ref<Indexbuffer> Create(const uint32_t Indices[], uint32_t Size);

		virtual ~Indexbuffer() = default;

	protected:
		uint32_t _Count;
	};
}
