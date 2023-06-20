#pragma once

namespace Volund
{
	class UniformBuffer
	{
	public:

		virtual void SetData(const void* data, uint32_t size, uint32_t offset) = 0;

		static Ref<UniformBuffer> Create(uint32_t size, uint32_t binding);

		virtual ~UniformBuffer();
	
	protected:

		uint32_t m_Id = 0;

	private:
	};
}

