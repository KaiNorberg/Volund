#pragma once

namespace Volund
{
	class UniformBuffer
	{
	public:

		template <typename T>
		void PushScalar(const std::string& name);

		template <typename T>
		void PushVector(const std::string& name);

		template <typename T>
		void PushMatrix(const std::string& name);

		virtual void Set(const std::string& name, const void* data) = 0;

		virtual void Allocate() = 0;

		virtual void Assign(uint32_t binding) = 0;

		static Ref<UniformBuffer> Create();

		virtual ~UniformBuffer();
	
	protected:

		struct Uniform
		{
			uint32_t DataSize;
			uint32_t Offset;
		};
		std::map<std::string, Uniform> m_Uniforms;

		uint32_t m_Size = 0;

		uint32_t m_Id = 0;

	private:
	};

	template<typename T>
	inline void UniformBuffer::PushScalar(const std::string& name)
	{
		constexpr uint32_t baseAlignment = sizeof(float);
		const uint32_t alignedOffset = Utils::RoundUp(this->m_Size, baseAlignment);
		m_Uniforms[name] = { sizeof(T), alignedOffset };
		this->m_Size = alignedOffset + baseAlignment;
	}

	template<typename T>
	inline void UniformBuffer::PushVector(const std::string& name)
	{
		constexpr uint32_t baseAlignment = 4 * sizeof(float);
		const uint32_t alignedOffset = Utils::RoundUp(this->m_Size, baseAlignment);
		m_Uniforms[name] = { sizeof(T), alignedOffset };
		this->m_Size = alignedOffset + baseAlignment;
	}

	template<typename T>
	inline void UniformBuffer::PushMatrix(const std::string& name)
	{
		constexpr uint32_t baseAlignment = 4 * sizeof(float);
		const uint32_t alignedOffset = Utils::RoundUp(this->m_Size, baseAlignment);
		m_Uniforms[name] = {sizeof(T), alignedOffset};
		this->m_Size = alignedOffset + 4 * baseAlignment;
	}
}

