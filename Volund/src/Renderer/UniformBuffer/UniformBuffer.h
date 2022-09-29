#pragma once

namespace Volund
{
	class UniformBuffer
	{
	public:

		template <typename T>
		void PushScalar(const std::string& Name);

		template <typename T>
		void PushVector(const std::string& Name);

		template <typename T>
		void PushMatrix(const std::string& Name);

		virtual void Set(const std::string& Name, const void* Data) = 0;

		virtual void Allocate(uint32_t Binding) = 0;

		static Ref<UniformBuffer> Create();

		virtual ~UniformBuffer();
	
	protected:

		struct Uniform
		{
			uint32_t DataSize;
			uint32_t BaseAlignment;
			uint32_t Offset;
		};
		std::map<std::string, Uniform> _Uniforms;

		uint32_t _Size = 0;

		uint32_t _ID = 0;

	private:
	};

	template<typename T>
	inline void UniformBuffer::PushScalar(const std::string& Name)
	{
		uint32_t BaseAlignment = sizeof(float);
		uint32_t AlignedOffset = Math::RoundUp(this->_Size, BaseAlignment);
		_Uniforms[Name] = { sizeof(T), BaseAlignment, AlignedOffset };
		this->_Size = AlignedOffset + BaseAlignment;
	}

	template<typename T>
	inline void UniformBuffer::PushVector(const std::string& Name)
	{
		uint32_t BaseAlignment = 4 * sizeof(float);
		uint32_t AlignedOffset = Math::RoundUp(this->_Size, BaseAlignment);
		_Uniforms[Name] = { sizeof(T), BaseAlignment, AlignedOffset };
		this->_Size = AlignedOffset + BaseAlignment;
	}

	template<typename T>
	inline void UniformBuffer::PushMatrix(const std::string& Name)
	{
		uint32_t BaseAlignment = 4 * sizeof(float);
		uint32_t AlignedOffset = Math::RoundUp(this->_Size, BaseAlignment);
		_Uniforms[Name] = {sizeof(T), 4 * BaseAlignment, AlignedOffset};
		this->_Size = AlignedOffset + 4 * BaseAlignment;
	}
}

