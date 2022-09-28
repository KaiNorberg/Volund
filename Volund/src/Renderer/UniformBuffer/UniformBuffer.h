#pragma once

namespace Volund
{
	class UniformBuffer
	{
	public:

		template <typename T>
		void Push(const std::string& Name);

		virtual void Set(const std::string& Name, const void* Data) = 0;

		virtual void Allocate(uint32_t Binding) = 0;

		static Ref<UniformBuffer> Create();

		virtual ~UniformBuffer();
	
	protected:

		struct Uniform
		{
			uint32_t Size;
			uint32_t Offset;
		};
		std::map<std::string, Uniform> _Uniforms;

		uint32_t _Size = 0;

		uint32_t _ID = 0;

	private:
	};

	template<typename T>
	inline void UniformBuffer::Push(const std::string& Name)
	{
		if (this->_ID == 0)
		{
			this->_Uniforms[Name] = { sizeof(T), this->_Size };
			this->_Size += sizeof(T);
		}
		else
		{
			VOLUND_INFO("UniformBuffer Already Allocated!");
		}
	}
}

