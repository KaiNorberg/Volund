#pragma once

namespace Volund
{
	class IndexBuffer
	{
	public:
		virtual void Bind() = 0;

		virtual void Unbind() = 0;

		uint32_t GetCount() const;

		static Ref<IndexBuffer> Create(const uint32_t indices[], uint32_t size);

		virtual ~IndexBuffer() = default;

	protected:
		uint32_t m_Count = 0;
	};
}
