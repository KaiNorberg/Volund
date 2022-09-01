#pragma once

namespace Volund
{
	class IndexBuffer
	{
	public:

		virtual void Bind() = 0;

		virtual void Unbind() = 0;

		uint32_t GetCount();

		static Ref<IndexBuffer> Create(uint32_t Indices[], uint32_t Size);

		virtual ~IndexBuffer() = default;

	protected:
		uint32_t _Count;
	};
}