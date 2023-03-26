#pragma once

namespace Volund
{
	class Indexbuffer
	{
	public:
		virtual void Bind() = 0;

		virtual void Unbind() = 0;

		uint32_t GetCount() const;

		static Ref<Indexbuffer> Create(const uint32_t indices[], uint32_t size);

		virtual ~Indexbuffer() = default;

	protected:
		uint32_t m_Count = 0;
	};
}
