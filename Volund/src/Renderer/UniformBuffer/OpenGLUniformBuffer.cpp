#include "PCH/PCH.h"
#include "OpenGLUniformBuffer.h"

#include <glad/include/glad/glad.h>

namespace Volund
{
	void OpenGLUniformBuffer::Set(const std::string& Name, const void* Data)
	{
		if (this->_ID != 0)
		{
			Uniform uniform = this->_Uniforms[Name];
			glNamedBufferSubData(this->_ID, uniform.Offset, uniform.Size, Data);
		}
		else
		{
			VOLUND_INFO("Uniform Buffer Not Allocated!");
		}
	}

	void OpenGLUniformBuffer::Allocate(uint32_t Binding)
	{
		glCreateBuffers(1, &this->_ID);
		glNamedBufferData(this->_ID, this->_Size, nullptr, GL_DYNAMIC_DRAW);
		glBindBufferBase(GL_UNIFORM_BUFFER, Binding, this->_ID);
	}

	OpenGLUniformBuffer::~OpenGLUniformBuffer()
	{
		if (this->_ID != 0)
		{
			glDeleteBuffers(1, &this->_ID);
		}
	}
}